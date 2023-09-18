// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: gateway.proto
#ifndef GRPC_gateway_2eproto__INCLUDED
#define GRPC_gateway_2eproto__INCLUDED

#include "gateway.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace ServerRpc {
namespace gateway {

class Gateway final {
 public:
  static constexpr char const* service_full_name() {
    return "ServerRpc.gateway.Gateway";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>> AsynconlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>>(AsynconlineBatchPushOneMsgRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>> PrepareAsynconlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>>(PrepareAsynconlineBatchPushOneMsgRaw(context, request, cq));
    }
    virtual ::grpc::Status kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::ServerRpc::gateway::kickUserResp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::kickUserResp>> AsynckickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::kickUserResp>>(AsynckickUserRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::kickUserResp>> PrepareAsynckickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::kickUserResp>>(PrepareAsynckickUserRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response, std::function<void(::grpc::Status)>) = 0;
      virtual void onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response, std::function<void(::grpc::Status)>) = 0;
      virtual void kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* AsynconlineBatchPushOneMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* PrepareAsynconlineBatchPushOneMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::kickUserResp>* AsynckickUserRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::gateway::kickUserResp>* PrepareAsynckickUserRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>> AsynconlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>>(AsynconlineBatchPushOneMsgRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>> PrepareAsynconlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>>(PrepareAsynconlineBatchPushOneMsgRaw(context, request, cq));
    }
    ::grpc::Status kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::ServerRpc::gateway::kickUserResp* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>> AsynckickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>>(AsynckickUserRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>> PrepareAsynckickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>>(PrepareAsynckickUserRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response, std::function<void(::grpc::Status)>) override;
      void onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response, ::grpc::ClientUnaryReactor* reactor) override;
      void kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response, std::function<void(::grpc::Status)>) override;
      void kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* AsynconlineBatchPushOneMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* PrepareAsynconlineBatchPushOneMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>* AsynckickUserRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>* PrepareAsynckickUserRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_onlineBatchPushOneMsg_;
    const ::grpc::internal::RpcMethod rpcmethod_kickUser_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status onlineBatchPushOneMsg(::grpc::ServerContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response);
    virtual ::grpc::Status kickUser(::grpc::ServerContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_onlineBatchPushOneMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_onlineBatchPushOneMsg() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_onlineBatchPushOneMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status onlineBatchPushOneMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* /*request*/, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestonlineBatchPushOneMsg(::grpc::ServerContext* context, ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::grpc::ServerAsyncResponseWriter< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_kickUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_kickUser() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_kickUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kickUser(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::kickUserReq* /*request*/, ::ServerRpc::gateway::kickUserResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestkickUser(::grpc::ServerContext* context, ::ServerRpc::gateway::kickUserReq* request, ::grpc::ServerAsyncResponseWriter< ::ServerRpc::gateway::kickUserResp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_onlineBatchPushOneMsg<WithAsyncMethod_kickUser<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_onlineBatchPushOneMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_onlineBatchPushOneMsg() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response) { return this->onlineBatchPushOneMsg(context, request, response); }));}
    void SetMessageAllocatorFor_onlineBatchPushOneMsg(
        ::grpc::MessageAllocator< ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_onlineBatchPushOneMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status onlineBatchPushOneMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* /*request*/, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* onlineBatchPushOneMsg(
      ::grpc::CallbackServerContext* /*context*/, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* /*request*/, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_kickUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_kickUser() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response) { return this->kickUser(context, request, response); }));}
    void SetMessageAllocatorFor_kickUser(
        ::grpc::MessageAllocator< ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_kickUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kickUser(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::kickUserReq* /*request*/, ::ServerRpc::gateway::kickUserResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* kickUser(
      ::grpc::CallbackServerContext* /*context*/, const ::ServerRpc::gateway::kickUserReq* /*request*/, ::ServerRpc::gateway::kickUserResp* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_onlineBatchPushOneMsg<WithCallbackMethod_kickUser<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_onlineBatchPushOneMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_onlineBatchPushOneMsg() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_onlineBatchPushOneMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status onlineBatchPushOneMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* /*request*/, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_kickUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_kickUser() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_kickUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kickUser(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::kickUserReq* /*request*/, ::ServerRpc::gateway::kickUserResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_onlineBatchPushOneMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_onlineBatchPushOneMsg() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_onlineBatchPushOneMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status onlineBatchPushOneMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* /*request*/, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestonlineBatchPushOneMsg(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_kickUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_kickUser() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_kickUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kickUser(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::kickUserReq* /*request*/, ::ServerRpc::gateway::kickUserResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestkickUser(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_onlineBatchPushOneMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_onlineBatchPushOneMsg() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->onlineBatchPushOneMsg(context, request, response); }));
    }
    ~WithRawCallbackMethod_onlineBatchPushOneMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status onlineBatchPushOneMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* /*request*/, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* onlineBatchPushOneMsg(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_kickUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_kickUser() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->kickUser(context, request, response); }));
    }
    ~WithRawCallbackMethod_kickUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status kickUser(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::kickUserReq* /*request*/, ::ServerRpc::gateway::kickUserResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* kickUser(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_onlineBatchPushOneMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_onlineBatchPushOneMsg() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* streamer) {
                       return this->StreamedonlineBatchPushOneMsg(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_onlineBatchPushOneMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status onlineBatchPushOneMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* /*request*/, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedonlineBatchPushOneMsg(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::ServerRpc::gateway::onlineBatchPushOneMsgReq,::ServerRpc::gateway::onlineBatchPushOneMsgResp>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_kickUser : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_kickUser() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp>* streamer) {
                       return this->StreamedkickUser(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_kickUser() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status kickUser(::grpc::ServerContext* /*context*/, const ::ServerRpc::gateway::kickUserReq* /*request*/, ::ServerRpc::gateway::kickUserResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedkickUser(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::ServerRpc::gateway::kickUserReq,::ServerRpc::gateway::kickUserResp>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_onlineBatchPushOneMsg<WithStreamedUnaryMethod_kickUser<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_onlineBatchPushOneMsg<WithStreamedUnaryMethod_kickUser<Service > > StreamedService;
};

}  // namespace gateway
}  // namespace ServerRpc


#endif  // GRPC_gateway_2eproto__INCLUDED
