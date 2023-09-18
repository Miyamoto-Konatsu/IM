// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: gateway.proto

#include "gateway.pb.h"
#include "gateway.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace ServerRpc {
namespace gateway {

static const char* Gateway_method_names[] = {
  "/ServerRpc.gateway.Gateway/onlineBatchPushOneMsg",
  "/ServerRpc.gateway.Gateway/kickUser",
};

std::unique_ptr< Gateway::Stub> Gateway::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Gateway::Stub> stub(new Gateway::Stub(channel, options));
  return stub;
}

Gateway::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_onlineBatchPushOneMsg_(Gateway_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_kickUser_(Gateway_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Gateway::Stub::onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_onlineBatchPushOneMsg_, context, request, response);
}

void Gateway::Stub::async::onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_onlineBatchPushOneMsg_, context, request, response, std::move(f));
}

void Gateway::Stub::async::onlineBatchPushOneMsg(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_onlineBatchPushOneMsg_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* Gateway::Stub::PrepareAsynconlineBatchPushOneMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::gateway::onlineBatchPushOneMsgResp, ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_onlineBatchPushOneMsg_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::onlineBatchPushOneMsgResp>* Gateway::Stub::AsynconlineBatchPushOneMsgRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynconlineBatchPushOneMsgRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Gateway::Stub::kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::ServerRpc::gateway::kickUserResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_kickUser_, context, request, response);
}

void Gateway::Stub::async::kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_kickUser_, context, request, response, std::move(f));
}

void Gateway::Stub::async::kickUser(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_kickUser_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>* Gateway::Stub::PrepareAsynckickUserRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::gateway::kickUserResp, ::ServerRpc::gateway::kickUserReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_kickUser_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::gateway::kickUserResp>* Gateway::Stub::AsynckickUserRaw(::grpc::ClientContext* context, const ::ServerRpc::gateway::kickUserReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynckickUserRaw(context, request, cq);
  result->StartCall();
  return result;
}

Gateway::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Gateway_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Gateway::Service, ::ServerRpc::gateway::onlineBatchPushOneMsgReq, ::ServerRpc::gateway::onlineBatchPushOneMsgResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Gateway::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* req,
             ::ServerRpc::gateway::onlineBatchPushOneMsgResp* resp) {
               return service->onlineBatchPushOneMsg(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Gateway_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Gateway::Service, ::ServerRpc::gateway::kickUserReq, ::ServerRpc::gateway::kickUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Gateway::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::gateway::kickUserReq* req,
             ::ServerRpc::gateway::kickUserResp* resp) {
               return service->kickUser(ctx, req, resp);
             }, this)));
}

Gateway::Service::~Service() {
}

::grpc::Status Gateway::Service::onlineBatchPushOneMsg(::grpc::ServerContext* context, const ::ServerRpc::gateway::onlineBatchPushOneMsgReq* request, ::ServerRpc::gateway::onlineBatchPushOneMsgResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Gateway::Service::kickUser(::grpc::ServerContext* context, const ::ServerRpc::gateway::kickUserReq* request, ::ServerRpc::gateway::kickUserResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace ServerRpc
}  // namespace gateway

