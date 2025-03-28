#!/usr/bin/env python

# Copyright (c) 2014-2017, The Regents of the University of California.
# Copyright (c) 2016-2017, Nefeli Networks, Inc.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# * Neither the names of the copyright holders nor the names of their
# contributors may be used to endorse or promote products derived from this
# software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

from __future__ import print_function

import glob
import sys
import os
import os.path
import re
import shlex
import subprocess
import textwrap
import argparse


def cmd(cmd, quiet=False, shell=False):
    """
    Run a command.  If quiet is True, or if V is not set in the
    environment, eat its stdout and stderr by default (we'll print
    both to stderr on any failure though).

    If V is set and we're not forced to be quiet, just let stdout
    and stderr flow through as usual.  The name V is from the
    standard Linux kernel build ("V=1 make" => print everything).

    (We use quiet=True for build environment test cleanup steps;
    the tests themselves use use cmd_success() to check for failures.)
    """
    if not quiet:
        quiet = os.getenv('V') is None

    kwargs = {'universal_newlines': True,
              'close_fds': False}  # For Python >3.2, default is True

    if quiet:
        kwargs['stdout'] = subprocess.PIPE
        kwargs['stderr'] = subprocess.STDOUT
    if shell:
        proc = subprocess.Popen(cmd, shell=True, **kwargs)
    else:
        proc = subprocess.Popen(shlex.split(cmd), **kwargs)

    # There is never any stderr output here - either it went straight
    # to os.STDERR_FILENO, or it went to the pipe for stdout.
    out, _ = proc.communicate()

    if proc.returncode:
        # We only have output if we ran in quiet mode.
        if quiet:
            print('Log:\n', out, file=sys.stderr)
        print('Error has occured running command: %s' % cmd, file=sys.stderr)
        sys.exit(proc.returncode)

    return out


BESS_DIR = os.path.dirname(os.path.abspath(__file__))

DEPS_DIR = '%s/deps' % BESS_DIR

DPDK_URL = 'https://fast.dpdk.org/rel'
DPDK_VER = 'dpdk-19.11.4'
DPDK_TARGET = 'x86_64-native-linuxapp-gcc'

kernel_release = cmd('uname -r', quiet=True).strip()

DPDK_DIR = '%s/%s' % (DEPS_DIR, DPDK_VER)
DPDK_CFLAGS = '"-g -w"'
DPDK_CONFIG = '%s/build/.config' % DPDK_DIR

extra_libs = set()
cxx_flags = []
ld_flags = []
plugins = []


def cmd_success(cmd):
    try:
        # This is a little sloppy - the pipes swallow up output,
        # but if the output exceeds PIPE_MAX, the pipes will
        # constipate and check_call may never return.
        subprocess.check_call(
            cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
        return True
    except subprocess.CalledProcessError:
        return False


def check_header(header_file, compiler):
    test_c_file = '%s/test.c' % DEPS_DIR
    test_o_file = '%s/test.o' % DEPS_DIR

    src = """
        #include <%s>

        int main()
        {
            return 0;
        }
        """ % header_file

    try:
        with open(test_c_file, 'w') as fp:
            fp.write(textwrap.dedent(src))

        return cmd_success('%s %s -c %s -o %s' %
                           (compiler, ' '.join(cxx_flags), test_c_file,
                            test_o_file))

    finally:
        cmd('rm -f %s %s' % (test_c_file, test_o_file), quiet=True)


def check_c_lib(lib):
    test_c_file = '%s/test.c' % DEPS_DIR
    test_e_file = '%s/test' % DEPS_DIR

    src = """
        int main()
        {
            return 0;
        }
        """

    try:
        with open(test_c_file, 'w') as fp:
            fp.write(textwrap.dedent(src))

        return cmd_success('gcc %s -l%s %s %s -o %s' %
                           (test_c_file, lib, ' '.join(cxx_flags),
                            ' '.join(ld_flags), test_e_file))
    finally:
        cmd('rm -f %s %s' % (test_c_file, test_e_file), quiet=True)


def required(header_file, lib_name, compiler):
    if not check_header(header_file, compiler):
        print('Error - #include <%s> failed. Did you install "%s" package?'
              % (header_file, lib_name), file=sys.stderr)
        sys.exit(1)


def check_essential():
    if not cmd_success('gcc -v'):
        print('Error - "gcc" is not available', file=sys.stderr)
        sys.exit(1)

    if not cmd_success('g++ -v'):
        print('Error - "g++" is not available', file=sys.stderr)
        sys.exit(1)

    if not cmd_success('make -v'):
        print('Error - "make" is not available', file=sys.stderr)
        sys.exit(1)

    required('numa.h', 'libnuma-dev', 'gcc')
    required('pcap/pcap.h', 'libpcap-dev', 'gcc')
    required('zlib.h', 'zlib1g-dev', 'gcc')
    required('glog/logging.h', 'libgoogle-glog-dev', 'g++')
    required('gflags/gflags.h', 'libgflags-dev', 'g++')
    required('gtest/gtest.h', 'libgtest-dev', 'g++')
    required('benchmark/benchmark.h', 'https://github.com/google/benchmark',
             'g++')


def set_config(filename, config, new_value):
    with open(filename) as fp:
        lines = fp.readlines()

    found = False
    with open(filename, 'w') as fp:
        for line in lines:
            if line.startswith(config + '='):
                found = True
                line = '%s=%s\n' % (config, new_value)
            fp.write(line)

    assert found, '"%s" is not found in %s' % (config, filename)
    print('  %s: %s=%s' % (filename, config, new_value))


def is_kernel_header_installed():
    return os.path.isdir("/lib/modules/%s/build" % kernel_release)


def check_kernel_headers():
    # If kernel header is not available, do not attempt to build
    # any components that require kernel.
    if not is_kernel_header_installed():
        set_config(DPDK_CONFIG, 'CONFIG_RTE_EAL_IGB_UIO', 'n')
        set_config(DPDK_CONFIG, 'CONFIG_RTE_KNI_KMOD', 'n')
        set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_KNI', 'n')
        set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_PMD_KNI', 'n')


def check_bnx():
    if check_header('zlib.h', 'gcc') and check_c_lib('z'):
        extra_libs.add('z')
    else:
        print(' - "zlib1g-dev" is not available. Disabling BNX2X PMD...')
        set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_BNX2X_PMD', 'n')


def check_mlx():
    # if check_header('infiniband/ib.h', 'gcc') and check_c_lib('mlx4') and \
    #         check_c_lib('mlx5'):
    #     extra_libs.add('ibverbs')
    #     extra_libs.add('mlx4')
    #     extra_libs.add('mlx5')
    # else:
    #     print(' - "Mellanox OFED" is not available. '
    #           'Disabling MLX4 and MLX5 PMDs...')
    #     if check_header('infiniband/verbs.h', 'gcc'):
    #         print('   NOTE: "libibverbs-dev" does exist, but it does not '
    #               'work with MLX PMDs. Instead download OFED from '
    #               'http://www.melloanox.com')

    ibverbs_avail = check_header('infiniband/ib.h', 'gcc')
    mlx4_avail = check_c_lib('mlx4')
    mlx5_avail = check_c_lib('mlx5')

    print('Checking Mellanox')
    
    if ibverbs_avail:
        if mlx4_avail:
            print(' Mellanox ML4 used')
            extra_libs.add('mlx4')
            set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_MLX4_PMD', 'y')
        else:
            print(" - Mellanox OFED: MLX4 PMD not available, disabling...")
            set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_MLX4_PMD', 'n')
        if mlx5_avail:
            print(' Mellanox MLX5 working')
            extra_libs.add('mlx5')
            set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_MLX5_PMD', 'y')
        else:
            print(" - Mellanox OFED: MLX5 PMD not available, disabling...")
            set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_MLX5_PMD', 'n')
        if mlx5_avail or mlx4_avail:
            extra_libs.add('ibverbs')
        else:
            print('   NOTE: "libibverbs-dev" does exist, but it does not '
                  'work with MLX PMDs. Instead download OFED from '
                  'http://www.melloanox.com')
    
    #     set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_MLX4_PMD', 'n')
    #     set_config(DPDK_CONFIG, 'CONFIG_RTE_LIBRTE_MLX5_PMD', 'n')


def generate_dpdk_extra_mk():
    with open('core/extra.dpdk.mk', 'w') as fp:
        fp.write('LIBS += %s\n' % ' '.join(['-l' + lib for lib in extra_libs]))


def find_current_plugins():
    "return list of existing plugins"
    result = []
    try:
        for line in open('core/extra.mk').readlines():
            match = re.match(r'PLUGINS \+= (.*)', line)
            if match:
                result.append(match.group(1))
    except (OSError, IOError):
        pass
    return result


def generate_extra_mk():
    "set up core/extra.mk to hold flags and plugin paths"
    with open('core/extra.mk', 'w') as fp:
        fp.write('CXXFLAGS += %s\n' % ' '.join(cxx_flags))
        fp.write('LDFLAGS += %s\n' % ' '.join(ld_flags))
        for path in plugins:
            fp.write('PLUGINS += {}\n'.format(path))


def download_dpdk(quiet=False):
    if os.path.exists(DPDK_DIR):
        if not quiet:
            print('already downloaded to %s' % DPDK_DIR)
        return
    try:
        cmd('mkdir -p %s' % DPDK_DIR)
        url = '%s/%s.tar.gz' % (DPDK_URL, DPDK_VER)
        print('Downloading %s ...  ' % url)
        cmd('curl -s -L %s | tar zx -C %s --strip-components 1' %
            (url, DPDK_DIR), shell=True)
    except:
        cmd('rm -rf %s' % (DPDK_DIR))
        raise


def configure_dpdk():
    print('Configuring DPDK...')
    cmd('make -C %s config T=%s' % (DPDK_DIR, DPDK_TARGET))

    check_kernel_headers()
    check_mlx()
    generate_dpdk_extra_mk()

    arch = os.getenv('CPU')
    if arch:
        print(' - Building DPDK with -march=%s' % arch)
        set_config(DPDK_CONFIG, "CONFIG_RTE_MACHINE", arch)


def makeflags():
    """
    Return flags to pass to (gnu) Make.  We want to send $MAKEFLAGS
    through if it's set, but annoyingly, we may have to put '-' in
    front: both "make -n" and "make -w" (aka "make --print-directory")
    leave $MAKEFLAGS starting without a hyphen.

    If $MAKEFLAGS is not already set, use "-j" and "-l" with the number of
    cpus printed by nproc.
    """
    # reuse cached value if we have one
    result = getattr(makeflags, 'result', None)
    if result is not None:
        return result
    # figure out correct value, then cache it
    result = os.getenv('MAKEFLAGS')
    if result is None:
        result = '-j%d' % int(cmd('nproc', quiet=True))
    elif result != "" and not result.startswith('-'):
        result = '-%s' % result
    makeflags.result = result
    return result


def build_dpdk():
    check_essential()
    download_dpdk(quiet=True)

    # not configured yet?
    #if not os.path.exists('%s/build' % DPDK_DIR):
    configure_dpdk()

    for f in glob.glob('%s/*.patch' % DEPS_DIR):
        print('Applying patch %s' % f)
        cmd('patch -d %s -N -p1 < %s || true' % (DPDK_DIR, f), shell=True)

    print('Building DPDK...')
    nproc = int(cmd('nproc', quiet=True))
    cmd('make -C %s EXTRA_CFLAGS=%s %s' % (DPDK_DIR,
                                           DPDK_CFLAGS,
                                           makeflags()))


def generate_protobuf_files():
    grpc = cmd('which grpc_python_plugin', quiet=True).strip()

    def gen_one_set_of_files(srcdir, outdir):
        "run protoc on *.proto in srcdir, with python output to outdir"
        cmd_template = ('protoc {name} --proto_path={srcdir} '
                        '--proto_path={stddir} '
                        '--python_out={outdir} --grpc_out={outdir} '
                        '--plugin=protoc-gen-grpc={grpc}')
        cmd_args = {
            'grpc': grpc,
            'stddir': 'protobuf',
            'srcdir': srcdir,
            'outdir': outdir,
        }
        files = glob.glob(os.path.join(srcdir, '*.proto'))
        for name in files:
            cmd(cmd_template.format(name=name, **cmd_args))
        # Note: when run as, e.g.
        #    protoc protobuf/ports/port_msg.proto \
        #        --proto_path=protobuf \
        #        --python_out=pybess/builtin_pb ...
        # protoc writes its output to:
        #    pybess/builtin_pb/ports/port_msg.proto
        # which is automatically where we want it.
        # Contrast this with bess/Makefile, where we put the
        # protobuf ports directory in another --proto_path argument,
        # so that the generated file does not have a ports/ prefix.
        # This is documented!  See, e.g.,
        # developers.google.com/protocol-buffers/docs/reference/cpp-generated
        files = glob.glob(os.path.join(srcdir, 'ports', '*.proto'))
        for name in files:
            cmd(cmd_template.format(name=name, **cmd_args))

    print('Generating protobuf codes for pybess...')
    sys.stdout.flush()
    gen_one_set_of_files('protobuf', 'pybess/builtin_pb')
    gen_one_set_of_files('protobuf/tests', 'pybess/builtin_pb')
    for path in plugins:
        gen_one_set_of_files(os.path.join(path, 'protobuf'),
                             'pybess/plugin_pb')


def build_bess():
    check_essential()

    if not os.path.exists('%s/build' % DPDK_DIR):
        build_dpdk()

    generate_protobuf_files()

    print('Building BESS daemon...')
    sys.stdout.flush()
    cmd('bin/bessctl daemon stop 2> /dev/null || true', shell=True)
    cmd('rm -f core/bessd')  # force relink as DPDK might have been rebuilt
    cmd('make -C core bessd modules all_test %s' % makeflags())


def build_kmod():
    check_essential()

    if os.getenv('KERNELDIR'):
        print('Building BESS kernel module (%s) ...' %
              os.getenv('KERNELDIR'))
    else:
        print('Building BESS kernel module (%s - running kernel) ...' %
              kernel_release)
        if not is_kernel_header_installed():
            print('"kernel-headers-%s" is not available. Build may fail.' %
                  kernel_release)
    sys.stdout.flush()
    cmd('sudo -n rmmod bess 2> /dev/null || true', shell=True)
    try:
        cmd('make -C core/kmod')
    except SystemExit:
        print('*** module build has failed.', file=sys.stderr)
        sys.exit(1)


def build_all():
    build_dpdk()
    build_bess()
    build_kmod()
    print('Done.')


def do_clean():
    print('Cleaning up...')
    cmd('make -C core clean')
    cmd('make -C core/kmod clean')
    for path in ('pybess/builtin_pb', 'pybess/plugin_pb'):
        cmd('rm -rf '
            '{path}/*_pb2.py* {path}/ports/*_pb2.py* '
            '{path}/__init__.pyc {path}/ports/__init__.pyc '
            '{path}/*_pb2_grpc.py* {path}/ports/*_pb2_grpc.py* '
            '{path}/__pycache__ {path}/ports/__pycache__'.format(path=path))
    cmd('rm -rf %s/build' % DPDK_DIR)


def do_dist_clean():
    do_clean()
    print('Removing 3rd-party libraries...')
    cmd('rm -rf %s' % (DPDK_DIR))


def print_usage(parser):
    parser.print_help(file=sys.stderr)
    sys.exit(2)


def update_benchmark_path(path):
    print('Specified benchmark path %s' % path)
    cxx_flags.extend(['-I%s/include' % (path)])
    ld_flags.extend(['-L%s/lib' % (path)])


def dedup(lst):
    "de-duplicate a list, retaining original order"
    d = {}
    result = []
    for item in lst:
        if item not in d:
            d[item] = True
            result.append(item)
    return result


def show_plugins():
    "show the current (perhaps just-now augmented) set of plugins"
    for path in plugins:
        print(path)


def main():
    os.chdir(BESS_DIR)
    parser = argparse.ArgumentParser(description='Build BESS')
    cmds = {
        'all': build_all,
        'download_dpdk': download_dpdk,
        'dpdk': build_dpdk,
        'bess': build_bess,
        'kmod': build_kmod,
        'clean': do_clean,
        'dist_clean': do_dist_clean,
        'help': lambda: print_usage(parser),
        'protobuf': generate_protobuf_files,
        'show_plugins': show_plugins,
    }
    # if foo_bar is a command allow foo-bar too
    for name in list(cmds.keys()):
        if '_' in name:
            cmds[name.replace('_', '-')] = cmds[name]
    cmdlist = sorted(cmds.keys())
    parser.add_argument(
        'action',
        metavar='action',
        nargs='?',
        default='all',
        choices=cmdlist,
        help='Action is one of ' + ', '.join(cmdlist))
    parser.add_argument(
        '--plugin',
        action='append',
        help='add a plugin source directory')
    parser.add_argument(
        '--reset-plugins',
        action='store_true',
        help='clear out existing plugin settings')
    # Note: unlike plugins, --with-benchmark must be specified each time
    # you build bess.
    parser.add_argument(
        '--with-benchmark',
        dest='benchmark_path',
        nargs=1,
        help='Location of benchmark library')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='enable verbose builds (same as env V=1)')
    args = parser.parse_args()

    newplugins = [] if args.reset_plugins else find_current_plugins()
    if args.plugin:
        newplugins.extend(args.plugin)
    # Convert to absolute path, de-duplicate, and set plugins.
    plugins.extend(dedup(os.path.abspath(i) for i in newplugins))

    if args.verbose:
        os.environ['V'] = '1'

    if args.benchmark_path:
        update_benchmark_path(args.benchmark_path[0])
    if not os.path.exists(DEPS_DIR):
        os.makedirs(DEPS_DIR)

    # TODO(torek): only update if needed
    generate_extra_mk()

    cmds[args.action]()


if __name__ == '__main__':
    try:
        sys.exit(main())
    except KeyboardInterrupt:
        sys.exit('\nInterrupted')
