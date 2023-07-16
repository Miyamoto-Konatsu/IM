// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: msg.proto
#ifndef GRPC_msg_2eproto__INCLUDED
#define GRPC_msg_2eproto__INCLUDED

#include "msg.pb.h"

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
namespace msg {

class Msg final {
 public:
  static constexpr char const* service_full_name() {
    return "ServerRpc.msg.Msg";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status sendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::ServerRpc::msg::sendMsgResp* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::msg::sendMsgResp>> AsyncsendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::msg::sendMsgResp>>(AsyncsendMsgRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::msg::sendMsgResp>> PrepareAsyncsendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::msg::sendMsgResp>>(PrepareAsyncsendMsgRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void sendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq* request, ::ServerRpc::msg::sendMsgResp* response, std::function<void(::grpc::Status)>) = 0;
      virtual void sendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq* request, ::ServerRpc::msg::sendMsgResp* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::msg::sendMsgResp>* AsyncsendMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::ServerRpc::msg::sendMsgResp>* PrepareAsyncsendMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status sendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::ServerRpc::msg::sendMsgResp* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::msg::sendMsgResp>> AsyncsendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::msg::sendMsgResp>>(AsyncsendMsgRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::msg::sendMsgResp>> PrepareAsyncsendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::ServerRpc::msg::sendMsgResp>>(PrepareAsyncsendMsgRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void sendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq* request, ::ServerRpc::msg::sendMsgResp* response, std::function<void(::grpc::Status)>) override;
      void sendMsg(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq* request, ::ServerRpc::msg::sendMsgResp* response, ::grpc::ClientUnaryReactor* reactor) override;
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
    ::grpc::ClientAsyncResponseReader< ::ServerRpc::msg::sendMsgResp>* AsyncsendMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::ServerRpc::msg::sendMsgResp>* PrepareAsyncsendMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::msg::sendMsgReq& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_sendMsg_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status sendMsg(::grpc::ServerContext* context, const ::ServerRpc::msg::sendMsgReq* request, ::ServerRpc::msg::sendMsgResp* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_sendMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_sendMsg() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_sendMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::msg::sendMsgReq* /*request*/, ::ServerRpc::msg::sendMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestsendMsg(::grpc::ServerContext* context, ::ServerRpc::msg::sendMsgReq* request, ::grpc::ServerAsyncResponseWriter< ::ServerRpc::msg::sendMsgResp>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_sendMsg<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_sendMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_sendMsg() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::ServerRpc::msg::sendMsgReq, ::ServerRpc::msg::sendMsgResp>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::ServerRpc::msg::sendMsgReq* request, ::ServerRpc::msg::sendMsgResp* response) { return this->sendMsg(context, request, response); }));}
    void SetMessageAllocatorFor_sendMsg(
        ::grpc::MessageAllocator< ::ServerRpc::msg::sendMsgReq, ::ServerRpc::msg::sendMsgResp>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::ServerRpc::msg::sendMsgReq, ::ServerRpc::msg::sendMsgResp>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_sendMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::msg::sendMsgReq* /*request*/, ::ServerRpc::msg::sendMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* sendMsg(
      ::grpc::CallbackServerContext* /*context*/, const ::ServerRpc::msg::sendMsgReq* /*request*/, ::ServerRpc::msg::sendMsgResp* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_sendMsg<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_sendMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_sendMsg() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_sendMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::msg::sendMsgReq* /*request*/, ::ServerRpc::msg::sendMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_sendMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_sendMsg() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_sendMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::msg::sendMsgReq* /*request*/, ::ServerRpc::msg::sendMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestsendMsg(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_sendMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_sendMsg() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->sendMsg(context, request, response); }));
    }
    ~WithRawCallbackMethod_sendMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status sendMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::msg::sendMsgReq* /*request*/, ::ServerRpc::msg::sendMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* sendMsg(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_sendMsg : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_sendMsg() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::ServerRpc::msg::sendMsgReq, ::ServerRpc::msg::sendMsgResp>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::ServerRpc::msg::sendMsgReq, ::ServerRpc::msg::sendMsgResp>* streamer) {
                       return this->StreamedsendMsg(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_sendMsg() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status sendMsg(::grpc::ServerContext* /*context*/, const ::ServerRpc::msg::sendMsgReq* /*request*/, ::ServerRpc::msg::sendMsgResp* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedsendMsg(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::ServerRpc::msg::sendMsgReq,::ServerRpc::msg::sendMsgResp>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_sendMsg<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_sendMsg<Service > StreamedService;
};

}  // namespace msg
}  // namespace ServerRpc


#endif  // GRPC_msg_2eproto__INCLUDED
