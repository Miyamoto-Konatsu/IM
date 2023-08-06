// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: user.proto

#include "user.pb.h"
#include "user.grpc.pb.h"

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
namespace user {

static const char* User_method_names[] = {
  "/ServerRpc.user.User/createUser",
  "/ServerRpc.user.User/getUser",
  "/ServerRpc.user.User/checkUser",
};

std::unique_ptr< User::Stub> User::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< User::Stub> stub(new User::Stub(channel, options));
  return stub;
}

User::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_createUser_(User_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_getUser_(User_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_checkUser_(User_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status User::Stub::createUser(::grpc::ClientContext* context, const ::ServerRpc::user::createUserReq& request, ::ServerRpc::user::createUserResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::user::createUserReq, ::ServerRpc::user::createUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_createUser_, context, request, response);
}

void User::Stub::async::createUser(::grpc::ClientContext* context, const ::ServerRpc::user::createUserReq* request, ::ServerRpc::user::createUserResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::user::createUserReq, ::ServerRpc::user::createUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_createUser_, context, request, response, std::move(f));
}

void User::Stub::async::createUser(::grpc::ClientContext* context, const ::ServerRpc::user::createUserReq* request, ::ServerRpc::user::createUserResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_createUser_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::user::createUserResp>* User::Stub::PrepareAsynccreateUserRaw(::grpc::ClientContext* context, const ::ServerRpc::user::createUserReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::user::createUserResp, ::ServerRpc::user::createUserReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_createUser_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::user::createUserResp>* User::Stub::AsynccreateUserRaw(::grpc::ClientContext* context, const ::ServerRpc::user::createUserReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccreateUserRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status User::Stub::getUser(::grpc::ClientContext* context, const ::ServerRpc::user::getUserReq& request, ::ServerRpc::user::getUserResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::user::getUserReq, ::ServerRpc::user::getUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_getUser_, context, request, response);
}

void User::Stub::async::getUser(::grpc::ClientContext* context, const ::ServerRpc::user::getUserReq* request, ::ServerRpc::user::getUserResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::user::getUserReq, ::ServerRpc::user::getUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_getUser_, context, request, response, std::move(f));
}

void User::Stub::async::getUser(::grpc::ClientContext* context, const ::ServerRpc::user::getUserReq* request, ::ServerRpc::user::getUserResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_getUser_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::user::getUserResp>* User::Stub::PrepareAsyncgetUserRaw(::grpc::ClientContext* context, const ::ServerRpc::user::getUserReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::user::getUserResp, ::ServerRpc::user::getUserReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_getUser_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::user::getUserResp>* User::Stub::AsyncgetUserRaw(::grpc::ClientContext* context, const ::ServerRpc::user::getUserReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncgetUserRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status User::Stub::checkUser(::grpc::ClientContext* context, const ::ServerRpc::user::checkUserReq& request, ::ServerRpc::user::checkUserResp* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ServerRpc::user::checkUserReq, ::ServerRpc::user::checkUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_checkUser_, context, request, response);
}

void User::Stub::async::checkUser(::grpc::ClientContext* context, const ::ServerRpc::user::checkUserReq* request, ::ServerRpc::user::checkUserResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ServerRpc::user::checkUserReq, ::ServerRpc::user::checkUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_checkUser_, context, request, response, std::move(f));
}

void User::Stub::async::checkUser(::grpc::ClientContext* context, const ::ServerRpc::user::checkUserReq* request, ::ServerRpc::user::checkUserResp* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_checkUser_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::user::checkUserResp>* User::Stub::PrepareAsynccheckUserRaw(::grpc::ClientContext* context, const ::ServerRpc::user::checkUserReq& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ServerRpc::user::checkUserResp, ::ServerRpc::user::checkUserReq, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_checkUser_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ServerRpc::user::checkUserResp>* User::Stub::AsynccheckUserRaw(::grpc::ClientContext* context, const ::ServerRpc::user::checkUserReq& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccheckUserRaw(context, request, cq);
  result->StartCall();
  return result;
}

User::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::ServerRpc::user::createUserReq, ::ServerRpc::user::createUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](User::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::user::createUserReq* req,
             ::ServerRpc::user::createUserResp* resp) {
               return service->createUser(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::ServerRpc::user::getUserReq, ::ServerRpc::user::getUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](User::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::user::getUserReq* req,
             ::ServerRpc::user::getUserResp* resp) {
               return service->getUser(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::ServerRpc::user::checkUserReq, ::ServerRpc::user::checkUserResp, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](User::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ServerRpc::user::checkUserReq* req,
             ::ServerRpc::user::checkUserResp* resp) {
               return service->checkUser(ctx, req, resp);
             }, this)));
}

User::Service::~Service() {
}

::grpc::Status User::Service::createUser(::grpc::ServerContext* context, const ::ServerRpc::user::createUserReq* request, ::ServerRpc::user::createUserResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status User::Service::getUser(::grpc::ServerContext* context, const ::ServerRpc::user::getUserReq* request, ::ServerRpc::user::getUserResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status User::Service::checkUser(::grpc::ServerContext* context, const ::ServerRpc::user::checkUserReq* request, ::ServerRpc::user::checkUserResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace ServerRpc
}  // namespace user
