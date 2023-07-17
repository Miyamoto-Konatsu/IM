// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg.proto

#include "msg.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = ::PROTOBUF_NAMESPACE_ID::internal;
namespace ServerRpc {
namespace msg {
template <typename>
PROTOBUF_CONSTEXPR msg::msg(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.fromuserid_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.touserid_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.content_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_.createtime_)*/ ::int64_t{0}

  , /*decltype(_impl_.seq_)*/ ::int64_t{0}

  , /*decltype(_impl_.platformid_)*/ 0

  , /*decltype(_impl_.msgtype_)*/ 0

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct msgDefaultTypeInternal {
  PROTOBUF_CONSTEXPR msgDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~msgDefaultTypeInternal() {}
  union {
    msg _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 msgDefaultTypeInternal _msg_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR sendMsgReq::sendMsgReq(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.msg_)*/nullptr} {}
struct sendMsgReqDefaultTypeInternal {
  PROTOBUF_CONSTEXPR sendMsgReqDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~sendMsgReqDefaultTypeInternal() {}
  union {
    sendMsgReq _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 sendMsgReqDefaultTypeInternal _sendMsgReq_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR sendMsgResp::sendMsgResp(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.sendtime_)*/ ::int64_t{0}

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct sendMsgRespDefaultTypeInternal {
  PROTOBUF_CONSTEXPR sendMsgRespDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~sendMsgRespDefaultTypeInternal() {}
  union {
    sendMsgResp _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 sendMsgRespDefaultTypeInternal _sendMsgResp_default_instance_;
}  // namespace msg
}  // namespace ServerRpc
static ::_pb::Metadata file_level_metadata_msg_2eproto[3];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_msg_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_msg_2eproto = nullptr;
const ::uint32_t TableStruct_msg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _impl_.fromuserid_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _impl_.touserid_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _impl_.content_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _impl_.createtime_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _impl_.seq_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _impl_.platformid_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::msg, _impl_.msgtype_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::sendMsgReq, _impl_._has_bits_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::sendMsgReq, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::sendMsgReq, _impl_.msg_),
    0,
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::sendMsgResp, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServerRpc::msg::sendMsgResp, _impl_.sendtime_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        { 0, -1, -1, sizeof(::ServerRpc::msg::msg)},
        { 15, 24, -1, sizeof(::ServerRpc::msg::sendMsgReq)},
        { 25, -1, -1, sizeof(::ServerRpc::msg::sendMsgResp)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::ServerRpc::msg::_msg_default_instance_._instance,
    &::ServerRpc::msg::_sendMsgReq_default_instance_._instance,
    &::ServerRpc::msg::_sendMsgResp_default_instance_._instance,
};
const char descriptor_table_protodef_msg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\tmsg.proto\022\rServerRpc.msg\"\202\001\n\003msg\022\022\n\nfr"
    "omUserID\030\001 \001(\t\022\020\n\010toUserID\030\002 \001(\t\022\017\n\007cont"
    "ent\030\003 \001(\014\022\022\n\ncreateTime\030\004 \001(\003\022\013\n\003seq\030\005 \001"
    "(\003\022\022\n\nplatformID\030\006 \001(\005\022\017\n\007msgType\030\007 \001(\005\""
    "-\n\nsendMsgReq\022\037\n\003msg\030\001 \001(\0132\022.ServerRpc.m"
    "sg.msg\"\037\n\013sendMsgResp\022\020\n\010sendTime\030\001 \001(\0032"
    "G\n\003Msg\022@\n\007sendMsg\022\031.ServerRpc.msg.sendMs"
    "gReq\032\032.ServerRpc.msg.sendMsgRespb\006proto3"
};
static ::absl::once_flag descriptor_table_msg_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_msg_2eproto = {
    false,
    false,
    320,
    descriptor_table_protodef_msg_2eproto,
    "msg.proto",
    &descriptor_table_msg_2eproto_once,
    nullptr,
    0,
    3,
    schemas,
    file_default_instances,
    TableStruct_msg_2eproto::offsets,
    file_level_metadata_msg_2eproto,
    file_level_enum_descriptors_msg_2eproto,
    file_level_service_descriptors_msg_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_msg_2eproto_getter() {
  return &descriptor_table_msg_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_msg_2eproto(&descriptor_table_msg_2eproto);
namespace ServerRpc {
namespace msg {
// ===================================================================

class msg::_Internal {
 public:
};

msg::msg(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ServerRpc.msg.msg)
}
msg::msg(const msg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  msg* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.fromuserid_) {}

    , decltype(_impl_.touserid_) {}

    , decltype(_impl_.content_) {}

    , decltype(_impl_.createtime_) {}

    , decltype(_impl_.seq_) {}

    , decltype(_impl_.platformid_) {}

    , decltype(_impl_.msgtype_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.fromuserid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.fromuserid_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_fromuserid().empty()) {
    _this->_impl_.fromuserid_.Set(from._internal_fromuserid(), _this->GetArenaForAllocation());
  }
  _impl_.touserid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.touserid_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_touserid().empty()) {
    _this->_impl_.touserid_.Set(from._internal_touserid(), _this->GetArenaForAllocation());
  }
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.content_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_content().empty()) {
    _this->_impl_.content_.Set(from._internal_content(), _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.createtime_, &from._impl_.createtime_,
    static_cast<::size_t>(reinterpret_cast<char*>(&_impl_.msgtype_) -
    reinterpret_cast<char*>(&_impl_.createtime_)) + sizeof(_impl_.msgtype_));
  // @@protoc_insertion_point(copy_constructor:ServerRpc.msg.msg)
}

inline void msg::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.fromuserid_) {}

    , decltype(_impl_.touserid_) {}

    , decltype(_impl_.content_) {}

    , decltype(_impl_.createtime_) { ::int64_t{0} }

    , decltype(_impl_.seq_) { ::int64_t{0} }

    , decltype(_impl_.platformid_) { 0 }

    , decltype(_impl_.msgtype_) { 0 }

    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.fromuserid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.fromuserid_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.touserid_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.touserid_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.content_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

msg::~msg() {
  // @@protoc_insertion_point(destructor:ServerRpc.msg.msg)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void msg::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.fromuserid_.Destroy();
  _impl_.touserid_.Destroy();
  _impl_.content_.Destroy();
}

void msg::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void msg::Clear() {
// @@protoc_insertion_point(message_clear_start:ServerRpc.msg.msg)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.fromuserid_.ClearToEmpty();
  _impl_.touserid_.ClearToEmpty();
  _impl_.content_.ClearToEmpty();
  ::memset(&_impl_.createtime_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.msgtype_) -
      reinterpret_cast<char*>(&_impl_.createtime_)) + sizeof(_impl_.msgtype_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* msg::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string fromUserID = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_fromuserid();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "ServerRpc.msg.msg.fromUserID"));
        } else {
          goto handle_unusual;
        }
        continue;
      // string toUserID = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_touserid();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "ServerRpc.msg.msg.toUserID"));
        } else {
          goto handle_unusual;
        }
        continue;
      // bytes content = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_content();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // int64 createTime = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 32)) {
          _impl_.createtime_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // int64 seq = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 40)) {
          _impl_.seq_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // int32 platformID = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 48)) {
          _impl_.platformid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // int32 msgType = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 56)) {
          _impl_.msgtype_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* msg::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServerRpc.msg.msg)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string fromUserID = 1;
  if (!this->_internal_fromuserid().empty()) {
    const std::string& _s = this->_internal_fromuserid();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "ServerRpc.msg.msg.fromUserID");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  // string toUserID = 2;
  if (!this->_internal_touserid().empty()) {
    const std::string& _s = this->_internal_touserid();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "ServerRpc.msg.msg.toUserID");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  // bytes content = 3;
  if (!this->_internal_content().empty()) {
    const std::string& _s = this->_internal_content();
    target = stream->WriteBytesMaybeAliased(3, _s, target);
  }

  // int64 createTime = 4;
  if (this->_internal_createtime() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(
        4, this->_internal_createtime(), target);
  }

  // int64 seq = 5;
  if (this->_internal_seq() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(
        5, this->_internal_seq(), target);
  }

  // int32 platformID = 6;
  if (this->_internal_platformid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(
        6, this->_internal_platformid(), target);
  }

  // int32 msgType = 7;
  if (this->_internal_msgtype() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(
        7, this->_internal_msgtype(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServerRpc.msg.msg)
  return target;
}

::size_t msg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServerRpc.msg.msg)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string fromUserID = 1;
  if (!this->_internal_fromuserid().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_fromuserid());
  }

  // string toUserID = 2;
  if (!this->_internal_touserid().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_touserid());
  }

  // bytes content = 3;
  if (!this->_internal_content().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
                                    this->_internal_content());
  }

  // int64 createTime = 4;
  if (this->_internal_createtime() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_createtime());
  }

  // int64 seq = 5;
  if (this->_internal_seq() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_seq());
  }

  // int32 platformID = 6;
  if (this->_internal_platformid() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_platformid());
  }

  // int32 msgType = 7;
  if (this->_internal_msgtype() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_msgtype());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData msg::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    msg::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*msg::GetClassData() const { return &_class_data_; }


void msg::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<msg*>(&to_msg);
  auto& from = static_cast<const msg&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ServerRpc.msg.msg)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_fromuserid().empty()) {
    _this->_internal_set_fromuserid(from._internal_fromuserid());
  }
  if (!from._internal_touserid().empty()) {
    _this->_internal_set_touserid(from._internal_touserid());
  }
  if (!from._internal_content().empty()) {
    _this->_internal_set_content(from._internal_content());
  }
  if (from._internal_createtime() != 0) {
    _this->_internal_set_createtime(from._internal_createtime());
  }
  if (from._internal_seq() != 0) {
    _this->_internal_set_seq(from._internal_seq());
  }
  if (from._internal_platformid() != 0) {
    _this->_internal_set_platformid(from._internal_platformid());
  }
  if (from._internal_msgtype() != 0) {
    _this->_internal_set_msgtype(from._internal_msgtype());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void msg::CopyFrom(const msg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServerRpc.msg.msg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool msg::IsInitialized() const {
  return true;
}

void msg::InternalSwap(msg* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.fromuserid_, lhs_arena,
                                       &other->_impl_.fromuserid_, rhs_arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.touserid_, lhs_arena,
                                       &other->_impl_.touserid_, rhs_arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.content_, lhs_arena,
                                       &other->_impl_.content_, rhs_arena);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(msg, _impl_.msgtype_)
      + sizeof(msg::_impl_.msgtype_)
      - PROTOBUF_FIELD_OFFSET(msg, _impl_.createtime_)>(
          reinterpret_cast<char*>(&_impl_.createtime_),
          reinterpret_cast<char*>(&other->_impl_.createtime_));
}

::PROTOBUF_NAMESPACE_ID::Metadata msg::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_msg_2eproto_getter, &descriptor_table_msg_2eproto_once,
      file_level_metadata_msg_2eproto[0]);
}
// ===================================================================

class sendMsgReq::_Internal {
 public:
  using HasBits = decltype(std::declval<sendMsgReq>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(sendMsgReq, _impl_._has_bits_);
  static const ::ServerRpc::msg::msg& msg(const sendMsgReq* msg);
  static void set_has_msg(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::ServerRpc::msg::msg&
sendMsgReq::_Internal::msg(const sendMsgReq* msg) {
  return *msg->_impl_.msg_;
}
sendMsgReq::sendMsgReq(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ServerRpc.msg.sendMsgReq)
}
sendMsgReq::sendMsgReq(const sendMsgReq& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  sendMsgReq* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.msg_){nullptr}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_impl_.msg_ = new ::ServerRpc::msg::msg(*from._impl_.msg_);
  }
  // @@protoc_insertion_point(copy_constructor:ServerRpc.msg.sendMsgReq)
}

inline void sendMsgReq::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.msg_){nullptr}
  };
}

sendMsgReq::~sendMsgReq() {
  // @@protoc_insertion_point(destructor:ServerRpc.msg.sendMsgReq)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void sendMsgReq::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete _impl_.msg_;
}

void sendMsgReq::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void sendMsgReq::Clear() {
// @@protoc_insertion_point(message_clear_start:ServerRpc.msg.sendMsgReq)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(_impl_.msg_ != nullptr);
    _impl_.msg_->Clear();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* sendMsgReq::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .ServerRpc.msg.msg msg = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_msg(), ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* sendMsgReq::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServerRpc.msg.sendMsgReq)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // .ServerRpc.msg.msg msg = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::msg(this),
        _Internal::msg(this).GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServerRpc.msg.sendMsgReq)
  return target;
}

::size_t sendMsgReq::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServerRpc.msg.sendMsgReq)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .ServerRpc.msg.msg msg = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.msg_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData sendMsgReq::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    sendMsgReq::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*sendMsgReq::GetClassData() const { return &_class_data_; }


void sendMsgReq::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<sendMsgReq*>(&to_msg);
  auto& from = static_cast<const sendMsgReq&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ServerRpc.msg.sendMsgReq)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_internal_mutable_msg()->::ServerRpc::msg::msg::MergeFrom(
        from._internal_msg());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void sendMsgReq::CopyFrom(const sendMsgReq& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServerRpc.msg.sendMsgReq)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool sendMsgReq::IsInitialized() const {
  return true;
}

void sendMsgReq::InternalSwap(sendMsgReq* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  swap(_impl_.msg_, other->_impl_.msg_);
}

::PROTOBUF_NAMESPACE_ID::Metadata sendMsgReq::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_msg_2eproto_getter, &descriptor_table_msg_2eproto_once,
      file_level_metadata_msg_2eproto[1]);
}
// ===================================================================

class sendMsgResp::_Internal {
 public:
};

sendMsgResp::sendMsgResp(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ServerRpc.msg.sendMsgResp)
}
sendMsgResp::sendMsgResp(const sendMsgResp& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(), _impl_(from._impl_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(
      from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:ServerRpc.msg.sendMsgResp)
}

inline void sendMsgResp::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.sendtime_) { ::int64_t{0} }

    , /*decltype(_impl_._cached_size_)*/{}
  };
}

sendMsgResp::~sendMsgResp() {
  // @@protoc_insertion_point(destructor:ServerRpc.msg.sendMsgResp)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void sendMsgResp::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
}

void sendMsgResp::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void sendMsgResp::Clear() {
// @@protoc_insertion_point(message_clear_start:ServerRpc.msg.sendMsgResp)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.sendtime_ = ::int64_t{0};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* sendMsgResp::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int64 sendTime = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 8)) {
          _impl_.sendtime_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* sendMsgResp::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServerRpc.msg.sendMsgResp)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 sendTime = 1;
  if (this->_internal_sendtime() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(
        1, this->_internal_sendtime(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServerRpc.msg.sendMsgResp)
  return target;
}

::size_t sendMsgResp::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServerRpc.msg.sendMsgResp)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 sendTime = 1;
  if (this->_internal_sendtime() != 0) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(
        this->_internal_sendtime());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData sendMsgResp::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    sendMsgResp::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*sendMsgResp::GetClassData() const { return &_class_data_; }


void sendMsgResp::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<sendMsgResp*>(&to_msg);
  auto& from = static_cast<const sendMsgResp&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ServerRpc.msg.sendMsgResp)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_sendtime() != 0) {
    _this->_internal_set_sendtime(from._internal_sendtime());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void sendMsgResp::CopyFrom(const sendMsgResp& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServerRpc.msg.sendMsgResp)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool sendMsgResp::IsInitialized() const {
  return true;
}

void sendMsgResp::InternalSwap(sendMsgResp* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);

  swap(_impl_.sendtime_, other->_impl_.sendtime_);
}

::PROTOBUF_NAMESPACE_ID::Metadata sendMsgResp::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_msg_2eproto_getter, &descriptor_table_msg_2eproto_once,
      file_level_metadata_msg_2eproto[2]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace msg
}  // namespace ServerRpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ServerRpc::msg::msg*
Arena::CreateMaybeMessage< ::ServerRpc::msg::msg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerRpc::msg::msg >(arena);
}
template<> PROTOBUF_NOINLINE ::ServerRpc::msg::sendMsgReq*
Arena::CreateMaybeMessage< ::ServerRpc::msg::sendMsgReq >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerRpc::msg::sendMsgReq >(arena);
}
template<> PROTOBUF_NOINLINE ::ServerRpc::msg::sendMsgResp*
Arena::CreateMaybeMessage< ::ServerRpc::msg::sendMsgResp >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerRpc::msg::sendMsgResp >(arena);
}
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
