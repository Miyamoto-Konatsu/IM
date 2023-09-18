#ifndef GATEWAY_GATEWAY_H
#define GATEWAY_GATEWAY_H
#include "gateway.pb.h"
#include "gateway.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
using grpc::Status;
using grpc::ClientContext;
using grpcChannel = grpc::Channel;
using ServerRpc::gateway::onlineBatchPushOneMsgReq;
using ServerRpc::gateway::onlineBatchPushOneMsgResp;
using ServerRpc::gateway::kickUserResp;
using ServerRpc::gateway::kickUserReq;

class GatewayClient {
public:
    GatewayClient(std::shared_ptr<grpcChannel> channel) :
        stub_(ServerRpc::gateway::Gateway::NewStub(channel)) {
    }

    Status onlineBatchPushOneMsg(const onlineBatchPushOneMsgReq &request,
                                 onlineBatchPushOneMsgResp *response) {
        ClientContext context;
        return stub_->onlineBatchPushOneMsg(&context, request, response);
    }

    Status kickUser(const kickUserReq &request, kickUserResp *response) {
        ClientContext context;
        return stub_->kickUser(&context, request, response);
    }
    
    static GatewayClient getGatewayClient() {
        auto insecureChannelCredentials = grpc::InsecureChannelCredentials();
        auto channel =
            grpc::CreateChannel("localhost:50054", insecureChannelCredentials);
        return GatewayClient(channel);
    }

private:
    std::unique_ptr<ServerRpc::gateway::Gateway::Stub> stub_;
};

#endif