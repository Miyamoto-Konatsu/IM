// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: auth.proto

#include "auth.pb.h"
#include "auth.grpc.pb.h"

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
namespace auth {

static const char* Auth_method_names[] = {
  "/ServerRpc.auth.Auth/userToken",
  "/ServerRpc.auth.Auth/forceLogout",
  "/ServerRpc.auth.Auth/parseToken",
};

std::unique_ptr< Auth::Stub> Auth::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Auth::Stub> stub(new Auth::Stub(channel, options));
  return stub;
}

Auth::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_userToken_(Auth_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_forceLogout_(Auth_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_parseToken_(Auth_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Auth::Stub::userToken(::grpc::ClientContext* context, const ::ServerRpc::auth::userTokenReq& request, ::ServerRpc::auth::userTokenResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::auth::userTokenReq, ::ServerRpc::auth::userTokenResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_userToken_, context, request, response);
}

void Auth::Stub::async::userToken(::grpc::ClientContext* context, const ::ServerRpc::auth::userTokenReq* request, ::ServerRpc::auth::userTokenResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::auth::userTokenReq, ::ServerRpc::auth::userTokenResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_userToken_, context, request, response, std::move(f));
}

void Auth::Stub::async::userToken(::grpc::ClientContext* context, const ::ServerRpc::auth::userTokenReq* request, ::ServerRpc::auth::userTokenResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_userToken_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::auth::userTokenResp>* Auth::Stub::PrepareAsyncuserTokenRaw(::grpc::ClientContext* context, const ::ServerRpc::auth::userTokenReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::auth::userTokenResp, ::ServerRpc::auth::userTokenReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_userToken_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::auth::userTokenResp>* Auth::Stub::AsyncuserTokenRaw(::grpc::ClientContext* context, const ::ServerRpc::auth::userTokenReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncuserTokenRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Auth::Stub::forceLogout(::grpc::ClientContext* context, const ::ServerRpc::auth::forceLogoutReq& request, ::ServerRpc::auth::forceLogoutResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::auth::forceLogoutReq, ::ServerRpc::auth::forceLogoutResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_forceLogout_, context, request, response);
}

void Auth::Stub::async::forceLogout(::grpc::ClientContext* context, const ::ServerRpc::auth::forceLogoutReq* request, ::ServerRpc::auth::forceLogoutResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::auth::forceLogoutReq, ::ServerRpc::auth::forceLogoutResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_forceLogout_, context, request, response, std::move(f));
}

void Auth::Stub::async::forceLogout(::grpc::ClientContext* context, const ::ServerRpc::auth::forceLogoutReq* request, ::ServerRpc::auth::forceLogoutResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_forceLogout_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::auth::forceLogoutResp>* Auth::Stub::PrepareAsyncforceLogoutRaw(::grpc::ClientContext* context, const ::ServerRpc::auth::forceLogoutReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::auth::forceLogoutResp, ::ServerRpc::auth::forceLogoutReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_forceLogout_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::auth::forceLogoutResp>* Auth::Stub::AsyncforceLogoutRaw(::grpc::ClientContext* context, const ::ServerRpc::auth::forceLogoutReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncforceLogoutRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Auth::Stub::parseToken(::grpc::ClientContext* context, const ::ServerRpc::auth::parseTokenReq& request, ::ServerRpc::auth::parseTokenResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::auth::parseTokenReq, ::ServerRpc::auth::parseTokenResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_parseToken_, context, request, response);
}

void Auth::Stub::async::parseToken(::grpc::ClientContext* context, const ::ServerRpc::auth::parseTokenReq* request, ::ServerRpc::auth::parseTokenResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::auth::parseTokenReq, ::ServerRpc::auth::parseTokenResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_parseToken_, context, request, response, std::move(f));
}

void Auth::Stub::async::parseToken(::grpc::ClientContext* context, const ::ServerRpc::auth::parseTokenReq* request, ::ServerRpc::auth::parseTokenResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_parseToken_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::auth::parseTokenResp>* Auth::Stub::PrepareAsyncparseTokenRaw(::grpc::ClientContext* context, const ::ServerRpc::auth::parseTokenReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::auth::parseTokenResp, ::ServerRpc::auth::parseTokenReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_parseToken_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::auth::parseTokenResp>* Auth::Stub::AsyncparseTokenRaw(::grpc::ClientContext* context, const ::ServerRpc::auth::parseTokenReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncparseTokenRaw(context, request, cq);
  result->StartCall();
  return result;
}

Auth::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Auth_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Auth::Service, ::ServerRpc::auth::userTokenReq, ::ServerRpc::auth::userTokenResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Auth::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::auth::userTokenReq* req,
             ::ServerRpc::auth::userTokenResp* resp) {
               return service->userToken(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Auth_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Auth::Service, ::ServerRpc::auth::forceLogoutReq, ::ServerRpc::auth::forceLogoutResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Auth::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::auth::forceLogoutReq* req,
             ::ServerRpc::auth::forceLogoutResp* resp) {
               return service->forceLogout(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Auth_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Auth::Service, ::ServerRpc::auth::parseTokenReq, ::ServerRpc::auth::parseTokenResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Auth::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::auth::parseTokenReq* req,
             ::ServerRpc::auth::parseTokenResp* resp) {
               return service->parseToken(ctx, req, resp);
             }, this)));
}

Auth::Service::~Service() {
}

::grpc::Status Auth::Service::userToken(::grpc::ServerContext* context, const ::ServerRpc::auth::userTokenReq* request, ::ServerRpc::auth::userTokenResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Auth::Service::forceLogout(::grpc::ServerContext* context, const ::ServerRpc::auth::forceLogoutReq* request, ::ServerRpc::auth::forceLogoutResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Auth::Service::parseToken(::grpc::ServerContext* context, const ::ServerRpc::auth::parseTokenReq* request, ::ServerRpc::auth::parseTokenResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace ServerRpc
}  // namespace auth

