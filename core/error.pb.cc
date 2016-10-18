// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: error.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "error.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace bess {

namespace {

const ::google::protobuf::Descriptor* Error_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Error_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_error_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_error_2eproto() {
  protobuf_AddDesc_error_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "error.proto");
  GOOGLE_CHECK(file != NULL);
  Error_descriptor_ = file->message_type(0);
  static const int Error_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Error, err_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Error, errmsg_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Error, details_),
  };
  Error_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      Error_descriptor_,
      Error::internal_default_instance(),
      Error_offsets_,
      -1,
      -1,
      -1,
      sizeof(Error),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Error, _internal_metadata_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_error_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      Error_descriptor_, Error::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_error_2eproto() {
  Error_default_instance_.Shutdown();
  delete Error_reflection_;
}

void protobuf_InitDefaults_error_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::GetEmptyString();
  Error_default_instance_.DefaultConstruct();
  Error_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_error_2eproto_once_);
void protobuf_InitDefaults_error_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_error_2eproto_once_,
                 &protobuf_InitDefaults_error_2eproto_impl);
}
void protobuf_AddDesc_error_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_error_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013error.proto\022\004bess\"5\n\005Error\022\013\n\003err\030\001 \001("
    "\005\022\016\n\006errmsg\030\002 \001(\t\022\017\n\007details\030\003 \001(\tb\006prot"
    "o3", 82);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "error.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_error_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_error_2eproto_once_);
void protobuf_AddDesc_error_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_error_2eproto_once_,
                 &protobuf_AddDesc_error_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_error_2eproto {
  StaticDescriptorInitializer_error_2eproto() {
    protobuf_AddDesc_error_2eproto();
  }
} static_descriptor_initializer_error_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Error::kErrFieldNumber;
const int Error::kErrmsgFieldNumber;
const int Error::kDetailsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Error::Error()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_error_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:bess.Error)
}

void Error::InitAsDefaultInstance() {
}

Error::Error(const Error& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:bess.Error)
}

void Error::SharedCtor() {
  errmsg_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  details_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  err_ = 0;
  _cached_size_ = 0;
}

Error::~Error() {
  // @@protoc_insertion_point(destructor:bess.Error)
  SharedDtor();
}

void Error::SharedDtor() {
  errmsg_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  details_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void Error::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Error::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Error_descriptor_;
}

const Error& Error::default_instance() {
  protobuf_InitDefaults_error_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<Error> Error_default_instance_;

Error* Error::New(::google::protobuf::Arena* arena) const {
  Error* n = new Error;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Error::Clear() {
// @@protoc_insertion_point(message_clear_start:bess.Error)
  err_ = 0;
  errmsg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  details_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool Error::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:bess.Error)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 err = 1;
      case 1: {
        if (tag == 8) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &err_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_errmsg;
        break;
      }

      // optional string errmsg = 2;
      case 2: {
        if (tag == 18) {
         parse_errmsg:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_errmsg()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->errmsg().data(), this->errmsg().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "bess.Error.errmsg"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_details;
        break;
      }

      // optional string details = 3;
      case 3: {
        if (tag == 26) {
         parse_details:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_details()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->details().data(), this->details().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "bess.Error.details"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:bess.Error)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:bess.Error)
  return false;
#undef DO_
}

void Error::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:bess.Error)
  // optional int32 err = 1;
  if (this->err() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->err(), output);
  }

  // optional string errmsg = 2;
  if (this->errmsg().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->errmsg().data(), this->errmsg().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "bess.Error.errmsg");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->errmsg(), output);
  }

  // optional string details = 3;
  if (this->details().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->details().data(), this->details().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "bess.Error.details");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->details(), output);
  }

  // @@protoc_insertion_point(serialize_end:bess.Error)
}

::google::protobuf::uint8* Error::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:bess.Error)
  // optional int32 err = 1;
  if (this->err() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->err(), target);
  }

  // optional string errmsg = 2;
  if (this->errmsg().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->errmsg().data(), this->errmsg().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "bess.Error.errmsg");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->errmsg(), target);
  }

  // optional string details = 3;
  if (this->details().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->details().data(), this->details().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "bess.Error.details");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->details(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:bess.Error)
  return target;
}

size_t Error::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:bess.Error)
  size_t total_size = 0;

  // optional int32 err = 1;
  if (this->err() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->err());
  }

  // optional string errmsg = 2;
  if (this->errmsg().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->errmsg());
  }

  // optional string details = 3;
  if (this->details().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->details());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Error::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:bess.Error)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const Error* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Error>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:bess.Error)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:bess.Error)
    UnsafeMergeFrom(*source);
  }
}

void Error::MergeFrom(const Error& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:bess.Error)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void Error::UnsafeMergeFrom(const Error& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.err() != 0) {
    set_err(from.err());
  }
  if (from.errmsg().size() > 0) {

    errmsg_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.errmsg_);
  }
  if (from.details().size() > 0) {

    details_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.details_);
  }
}

void Error::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:bess.Error)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Error::CopyFrom(const Error& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:bess.Error)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool Error::IsInitialized() const {

  return true;
}

void Error::Swap(Error* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Error::InternalSwap(Error* other) {
  std::swap(err_, other->err_);
  errmsg_.Swap(&other->errmsg_);
  details_.Swap(&other->details_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Error::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Error_descriptor_;
  metadata.reflection = Error_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Error

// optional int32 err = 1;
void Error::clear_err() {
  err_ = 0;
}
::google::protobuf::int32 Error::err() const {
  // @@protoc_insertion_point(field_get:bess.Error.err)
  return err_;
}
void Error::set_err(::google::protobuf::int32 value) {
  
  err_ = value;
  // @@protoc_insertion_point(field_set:bess.Error.err)
}

// optional string errmsg = 2;
void Error::clear_errmsg() {
  errmsg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& Error::errmsg() const {
  // @@protoc_insertion_point(field_get:bess.Error.errmsg)
  return errmsg_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Error::set_errmsg(const ::std::string& value) {
  
  errmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:bess.Error.errmsg)
}
void Error::set_errmsg(const char* value) {
  
  errmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:bess.Error.errmsg)
}
void Error::set_errmsg(const char* value, size_t size) {
  
  errmsg_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:bess.Error.errmsg)
}
::std::string* Error::mutable_errmsg() {
  
  // @@protoc_insertion_point(field_mutable:bess.Error.errmsg)
  return errmsg_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Error::release_errmsg() {
  // @@protoc_insertion_point(field_release:bess.Error.errmsg)
  
  return errmsg_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Error::set_allocated_errmsg(::std::string* errmsg) {
  if (errmsg != NULL) {
    
  } else {
    
  }
  errmsg_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), errmsg);
  // @@protoc_insertion_point(field_set_allocated:bess.Error.errmsg)
}

// optional string details = 3;
void Error::clear_details() {
  details_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& Error::details() const {
  // @@protoc_insertion_point(field_get:bess.Error.details)
  return details_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Error::set_details(const ::std::string& value) {
  
  details_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:bess.Error.details)
}
void Error::set_details(const char* value) {
  
  details_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:bess.Error.details)
}
void Error::set_details(const char* value, size_t size) {
  
  details_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:bess.Error.details)
}
::std::string* Error::mutable_details() {
  
  // @@protoc_insertion_point(field_mutable:bess.Error.details)
  return details_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Error::release_details() {
  // @@protoc_insertion_point(field_release:bess.Error.details)
  
  return details_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Error::set_allocated_details(::std::string* details) {
  if (details != NULL) {
    
  } else {
    
  }
  details_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), details);
  // @@protoc_insertion_point(field_set_allocated:bess.Error.details)
}

inline const Error* Error::internal_default_instance() {
  return &Error_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace bess

// @@protoc_insertion_point(global_scope)
