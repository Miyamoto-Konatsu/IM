// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gateway.proto

#include "gateway.pb.h"

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
namespace gateway {
template <typename>
PROTOBUF_CONSTEXPR pushMessage_MsgsEntry_DoNotUse::pushMessage_MsgsEntry_DoNotUse(
    ::_pbi::ConstantInitialized) {}
struct pushMessage_MsgsEntry_DoNotUseDefaultTypeInternal {
  PROTOBUF_CONSTEXPR pushMessage_MsgsEntry_DoNotUseDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~pushMessage_MsgsEntry_DoNotUseDefaultTypeInternal() {}
  union {
    pushMessage_MsgsEntry_DoNotUse _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 pushMessage_MsgsEntry_DoNotUseDefaultTypeInternal _pushMessage_MsgsEntry_DoNotUse_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR pushMessage::pushMessage(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.msgs_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct pushMessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR pushMessageDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~pushMessageDefaultTypeInternal() {}
  union {
    pushMessage _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 pushMessageDefaultTypeInternal _pushMessage_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR onlineBatchPushOneMsgReq::onlineBatchPushOneMsgReq(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.pushtouserids_)*/{}
  , /*decltype(_impl_.msg_data_)*/nullptr} {}
struct onlineBatchPushOneMsgReqDefaultTypeInternal {
  PROTOBUF_CONSTEXPR onlineBatchPushOneMsgReqDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~onlineBatchPushOneMsgReqDefaultTypeInternal() {}
  union {
    onlineBatchPushOneMsgReq _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 onlineBatchPushOneMsgReqDefaultTypeInternal _onlineBatchPushOneMsgReq_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR onlineBatchPushOneMsgResp::onlineBatchPushOneMsgResp(
    ::_pbi::ConstantInitialized) {}
struct onlineBatchPushOneMsgRespDefaultTypeInternal {
  PROTOBUF_CONSTEXPR onlineBatchPushOneMsgRespDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~onlineBatchPushOneMsgRespDefaultTypeInternal() {}
  union {
    onlineBatchPushOneMsgResp _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 onlineBatchPushOneMsgRespDefaultTypeInternal _onlineBatchPushOneMsgResp_default_instance_;
}  // namespace gateway
}  // namespace ServerRpc
static ::_pb::Metadata file_level_metadata_gateway_2eproto[4];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_gateway_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_gateway_2eproto = nullptr;
const ::uint32_t TableStruct_gateway_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse, _has_bits_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse, key_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse, value_),
    0,
    1,
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::pushMessage, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::pushMessage, _impl_.msgs_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::onlineBatchPushOneMsgReq, _impl_._has_bits_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::onlineBatchPushOneMsgReq, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::onlineBatchPushOneMsgReq, _impl_.msg_data_),
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::onlineBatchPushOneMsgReq, _impl_.pushtouserids_),
    0,
    ~0u,
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::ServerRpc::gateway::onlineBatchPushOneMsgResp, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        { 0, 10, -1, sizeof(::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse)},
        { 12, -1, -1, sizeof(::ServerRpc::gateway::pushMessage)},
        { 21, 31, -1, sizeof(::ServerRpc::gateway::onlineBatchPushOneMsgReq)},
        { 33, -1, -1, sizeof(::ServerRpc::gateway::onlineBatchPushOneMsgResp)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::ServerRpc::gateway::_pushMessage_MsgsEntry_DoNotUse_default_instance_._instance,
    &::ServerRpc::gateway::_pushMessage_default_instance_._instance,
    &::ServerRpc::gateway::_onlineBatchPushOneMsgReq_default_instance_._instance,
    &::ServerRpc::gateway::_onlineBatchPushOneMsgResp_default_instance_._instance,
};
const char descriptor_table_protodef_gateway_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\rgateway.proto\022\021ServerRpc.gateway\032\tmsg."
    "proto\"\213\001\n\013pushMessage\0226\n\004msgs\030\001 \003(\0132(.Se"
    "rverRpc.gateway.pushMessage.MsgsEntry\032D\n"
    "\tMsgsEntry\022\013\n\003key\030\001 \001(\t\022&\n\005value\030\002 \001(\0132\027"
    ".ServerRpc.msg.pullMsgs:\0028\001\"W\n\030onlineBat"
    "chPushOneMsgReq\022$\n\010msg_data\030\001 \001(\0132\022.Serv"
    "erRpc.msg.msg\022\025\n\rpushToUserIDs\030\002 \003(\t\"\033\n\031"
    "onlineBatchPushOneMsgResp2}\n\007Gateway\022r\n\025"
    "onlineBatchPushOneMsg\022+.ServerRpc.gatewa"
    "y.onlineBatchPushOneMsgReq\032,.ServerRpc.g"
    "ateway.onlineBatchPushOneMsgRespb\006proto3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_gateway_2eproto_deps[1] =
    {
        &::descriptor_table_msg_2eproto,
};
static ::absl::once_flag descriptor_table_gateway_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_gateway_2eproto = {
    false,
    false,
    440,
    descriptor_table_protodef_gateway_2eproto,
    "gateway.proto",
    &descriptor_table_gateway_2eproto_once,
    descriptor_table_gateway_2eproto_deps,
    1,
    4,
    schemas,
    file_default_instances,
    TableStruct_gateway_2eproto::offsets,
    file_level_metadata_gateway_2eproto,
    file_level_enum_descriptors_gateway_2eproto,
    file_level_service_descriptors_gateway_2eproto,
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
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_gateway_2eproto_getter() {
  return &descriptor_table_gateway_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_gateway_2eproto(&descriptor_table_gateway_2eproto);
namespace ServerRpc {
namespace gateway {
// ===================================================================

pushMessage_MsgsEntry_DoNotUse::pushMessage_MsgsEntry_DoNotUse() {}
pushMessage_MsgsEntry_DoNotUse::pushMessage_MsgsEntry_DoNotUse(::PROTOBUF_NAMESPACE_ID::Arena* arena)
    : SuperType(arena) {}
void pushMessage_MsgsEntry_DoNotUse::MergeFrom(const pushMessage_MsgsEntry_DoNotUse& other) {
  MergeFromInternal(other);
}
::PROTOBUF_NAMESPACE_ID::Metadata pushMessage_MsgsEntry_DoNotUse::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_gateway_2eproto_getter, &descriptor_table_gateway_2eproto_once,
      file_level_metadata_gateway_2eproto[0]);
}
// ===================================================================

class pushMessage::_Internal {
 public:
};

void pushMessage::clear_msgs() {
  _impl_.msgs_.Clear();
}
pushMessage::pushMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ServerRpc.gateway.pushMessage)
}
pushMessage::pushMessage(const pushMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  pushMessage* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      /*decltype(_impl_.msgs_)*/{}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.msgs_.MergeFrom(from._impl_.msgs_);
  // @@protoc_insertion_point(copy_constructor:ServerRpc.gateway.pushMessage)
}

inline void pushMessage::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      /*decltype(_impl_.msgs_)*/{::_pbi::ArenaInitialized(), arena}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

pushMessage::~pushMessage() {
  // @@protoc_insertion_point(destructor:ServerRpc.gateway.pushMessage)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void pushMessage::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.msgs_.~MapField();
}

void pushMessage::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void pushMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:ServerRpc.gateway.pushMessage)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.msgs_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* pushMessage::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // map<string, .ServerRpc.msg.pullMsgs> msgs = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(&_impl_.msgs_, ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
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

::uint8_t* pushMessage::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServerRpc.gateway.pushMessage)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // map<string, .ServerRpc.msg.pullMsgs> msgs = 1;
  if (!this->_internal_msgs().empty()) {
    using MapType = ::_pb::Map<std::string, ::ServerRpc::msg::pullMsgs>;
    using WireHelper = pushMessage_MsgsEntry_DoNotUse::Funcs;
    const auto& map_field = this->_internal_msgs();
    auto check_utf8 = [](const MapType::value_type& entry) {
      (void)entry;
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
          entry.first.data(), static_cast<int>(entry.first.length()),
 ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "ServerRpc.gateway.pushMessage.msgs");
    };

    if (stream->IsSerializationDeterministic() && map_field.size() > 1) {
      for (const auto& entry : ::_pbi::MapSorterPtr<MapType>(map_field)) {
        target = WireHelper::InternalSerialize(1, entry.first, entry.second, target, stream);
        check_utf8(entry);
      }
    } else {
      for (const auto& entry : map_field) {
        target = WireHelper::InternalSerialize(1, entry.first, entry.second, target, stream);
        check_utf8(entry);
      }
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServerRpc.gateway.pushMessage)
  return target;
}

::size_t pushMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServerRpc.gateway.pushMessage)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // map<string, .ServerRpc.msg.pullMsgs> msgs = 1;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_msgs_size());
  for (::PROTOBUF_NAMESPACE_ID::Map< std::string, ::ServerRpc::msg::pullMsgs >::const_iterator
      it = this->_internal_msgs().begin();
      it != this->_internal_msgs().end(); ++it) {
    total_size += pushMessage_MsgsEntry_DoNotUse::Funcs::ByteSizeLong(it->first, it->second);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData pushMessage::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    pushMessage::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*pushMessage::GetClassData() const { return &_class_data_; }


void pushMessage::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<pushMessage*>(&to_msg);
  auto& from = static_cast<const pushMessage&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ServerRpc.gateway.pushMessage)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.msgs_.MergeFrom(from._impl_.msgs_);
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void pushMessage::CopyFrom(const pushMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServerRpc.gateway.pushMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool pushMessage::IsInitialized() const {
  return true;
}

void pushMessage::InternalSwap(pushMessage* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.msgs_.InternalSwap(&other->_impl_.msgs_);
}

::PROTOBUF_NAMESPACE_ID::Metadata pushMessage::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_gateway_2eproto_getter, &descriptor_table_gateway_2eproto_once,
      file_level_metadata_gateway_2eproto[1]);
}
// ===================================================================

class onlineBatchPushOneMsgReq::_Internal {
 public:
  using HasBits = decltype(std::declval<onlineBatchPushOneMsgReq>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(onlineBatchPushOneMsgReq, _impl_._has_bits_);
  static const ::ServerRpc::msg::msg& msg_data(const onlineBatchPushOneMsgReq* msg);
  static void set_has_msg_data(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::ServerRpc::msg::msg&
onlineBatchPushOneMsgReq::_Internal::msg_data(const onlineBatchPushOneMsgReq* msg) {
  return *msg->_impl_.msg_data_;
}
void onlineBatchPushOneMsgReq::clear_msg_data() {
  if (_impl_.msg_data_ != nullptr) _impl_.msg_data_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
onlineBatchPushOneMsgReq::onlineBatchPushOneMsgReq(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:ServerRpc.gateway.onlineBatchPushOneMsgReq)
}
onlineBatchPushOneMsgReq::onlineBatchPushOneMsgReq(const onlineBatchPushOneMsgReq& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  onlineBatchPushOneMsgReq* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.pushtouserids_){from._impl_.pushtouserids_}
    , decltype(_impl_.msg_data_){nullptr}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_impl_.msg_data_ = new ::ServerRpc::msg::msg(*from._impl_.msg_data_);
  }
  // @@protoc_insertion_point(copy_constructor:ServerRpc.gateway.onlineBatchPushOneMsgReq)
}

inline void onlineBatchPushOneMsgReq::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.pushtouserids_){arena}
    , decltype(_impl_.msg_data_){nullptr}
  };
}

onlineBatchPushOneMsgReq::~onlineBatchPushOneMsgReq() {
  // @@protoc_insertion_point(destructor:ServerRpc.gateway.onlineBatchPushOneMsgReq)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void onlineBatchPushOneMsgReq::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _internal_mutable_pushtouserids()->~RepeatedPtrField();
  if (this != internal_default_instance()) delete _impl_.msg_data_;
}

void onlineBatchPushOneMsgReq::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void onlineBatchPushOneMsgReq::Clear() {
// @@protoc_insertion_point(message_clear_start:ServerRpc.gateway.onlineBatchPushOneMsgReq)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_mutable_pushtouserids()->Clear();
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(_impl_.msg_data_ != nullptr);
    _impl_.msg_data_->Clear();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* onlineBatchPushOneMsgReq::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .ServerRpc.msg.msg msg_data = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_msg_data(), ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // repeated string pushToUserIDs = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_pushtouserids();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            CHK_(::_pbi::VerifyUTF8(str, "ServerRpc.gateway.onlineBatchPushOneMsgReq.pushToUserIDs"));
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
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

::uint8_t* onlineBatchPushOneMsgReq::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ServerRpc.gateway.onlineBatchPushOneMsgReq)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // .ServerRpc.msg.msg msg_data = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, _Internal::msg_data(this),
        _Internal::msg_data(this).GetCachedSize(), target, stream);
  }

  // repeated string pushToUserIDs = 2;
  for (int i = 0, n = this->_internal_pushtouserids_size(); i < n; ++i) {
    const auto& s = this->_internal_pushtouserids(i);
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        s.data(), static_cast<int>(s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "ServerRpc.gateway.onlineBatchPushOneMsgReq.pushToUserIDs");
    target = stream->WriteString(2, s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ServerRpc.gateway.onlineBatchPushOneMsgReq)
  return target;
}

::size_t onlineBatchPushOneMsgReq::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ServerRpc.gateway.onlineBatchPushOneMsgReq)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string pushToUserIDs = 2;
  total_size += 1 * ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_internal_pushtouserids().size());
  for (int i = 0, n = _internal_pushtouserids().size(); i < n; ++i) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        _internal_pushtouserids().Get(i));
  }

  // .ServerRpc.msg.msg msg_data = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.msg_data_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData onlineBatchPushOneMsgReq::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    onlineBatchPushOneMsgReq::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*onlineBatchPushOneMsgReq::GetClassData() const { return &_class_data_; }


void onlineBatchPushOneMsgReq::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<onlineBatchPushOneMsgReq*>(&to_msg);
  auto& from = static_cast<const onlineBatchPushOneMsgReq&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:ServerRpc.gateway.onlineBatchPushOneMsgReq)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_pushtouserids()->MergeFrom(from._internal_pushtouserids());
  if ((from._impl_._has_bits_[0] & 0x00000001u) != 0) {
    _this->_internal_mutable_msg_data()->::ServerRpc::msg::msg::MergeFrom(
        from._internal_msg_data());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void onlineBatchPushOneMsgReq::CopyFrom(const onlineBatchPushOneMsgReq& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ServerRpc.gateway.onlineBatchPushOneMsgReq)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool onlineBatchPushOneMsgReq::IsInitialized() const {
  return true;
}

void onlineBatchPushOneMsgReq::InternalSwap(onlineBatchPushOneMsgReq* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  _internal_mutable_pushtouserids()->InternalSwap(
      other->_internal_mutable_pushtouserids());
  swap(_impl_.msg_data_, other->_impl_.msg_data_);
}

::PROTOBUF_NAMESPACE_ID::Metadata onlineBatchPushOneMsgReq::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_gateway_2eproto_getter, &descriptor_table_gateway_2eproto_once,
      file_level_metadata_gateway_2eproto[2]);
}
// ===================================================================

class onlineBatchPushOneMsgResp::_Internal {
 public:
};

onlineBatchPushOneMsgResp::onlineBatchPushOneMsgResp(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase(arena) {
  // @@protoc_insertion_point(arena_constructor:ServerRpc.gateway.onlineBatchPushOneMsgResp)
}
onlineBatchPushOneMsgResp::onlineBatchPushOneMsgResp(const onlineBatchPushOneMsgResp& from)
  : ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase() {
  onlineBatchPushOneMsgResp* const _this = this; (void)_this;
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:ServerRpc.gateway.onlineBatchPushOneMsgResp)
}





const ::PROTOBUF_NAMESPACE_ID::Message::ClassData onlineBatchPushOneMsgResp::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::CopyImpl,
    ::PROTOBUF_NAMESPACE_ID::internal::ZeroFieldsBase::MergeImpl,
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*onlineBatchPushOneMsgResp::GetClassData() const { return &_class_data_; }







::PROTOBUF_NAMESPACE_ID::Metadata onlineBatchPushOneMsgResp::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_gateway_2eproto_getter, &descriptor_table_gateway_2eproto_once,
      file_level_metadata_gateway_2eproto[3]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace gateway
}  // namespace ServerRpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse*
Arena::CreateMaybeMessage< ::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerRpc::gateway::pushMessage_MsgsEntry_DoNotUse >(arena);
}
template<> PROTOBUF_NOINLINE ::ServerRpc::gateway::pushMessage*
Arena::CreateMaybeMessage< ::ServerRpc::gateway::pushMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerRpc::gateway::pushMessage >(arena);
}
template<> PROTOBUF_NOINLINE ::ServerRpc::gateway::onlineBatchPushOneMsgReq*
Arena::CreateMaybeMessage< ::ServerRpc::gateway::onlineBatchPushOneMsgReq >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerRpc::gateway::onlineBatchPushOneMsgReq >(arena);
}
template<> PROTOBUF_NOINLINE ::ServerRpc::gateway::onlineBatchPushOneMsgResp*
Arena::CreateMaybeMessage< ::ServerRpc::gateway::onlineBatchPushOneMsgResp >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ServerRpc::gateway::onlineBatchPushOneMsgResp >(arena);
}
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"