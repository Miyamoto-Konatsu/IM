#ifndef RPCSERVICE_GATEWAYRPC_H
#define RPCSERVICE_GATEWAYRPC_H

#include "gateway.grpc.pb.h"
#include "gateway.pb.h"
#include <grpcpp/grpcpp.h>
#include <memory>
class ChatServer;
using grpc::ServerContext;
using grpc::Status;
using ServerRpc::gateway::Gateway;
using namespace ServerRpc::gateway;

class GatewayServiceImpl final : public Gateway::Service {
public:
    GatewayServiceImpl(std::shared_ptr<ChatServer> chatServer) :
        chatServer_(chatServer) {
    }
    Status onlineBatchPushOneMsg(ServerContext *context,
                                 const onlineBatchPushOneMsgReq *request,
                                 onlineBatchPushOneMsgResp *response) override;

    static void startServer(std::shared_ptr<ChatServer> chatServer);
    
private:
    std::shared_ptr<ChatServer> chatServer_;
};

#endif