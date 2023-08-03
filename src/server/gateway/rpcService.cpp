#include "rpcService.h"
#include "protobuf/json/json.h"
#include "server.h"
#include <google/protobuf/util/json_util.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <muduo/base/Logging.h>
#include <thread>

using google::protobuf::util::JsonPrintOptions;
using grpc::ServerBuilder;

Status GatewayServiceImpl::onlineBatchPushOneMsg(
    ServerContext *context, const onlineBatchPushOneMsgReq *request,
    onlineBatchPushOneMsgResp *response) {
    for (auto pushToUserId : request->pushtouserids()) {
        auto clients = chatServer_->getClientMap().find(pushToUserId);
        for (auto client : clients) { client->pushMsg(&request->msg_data()); }
        // chatServer_->send(client->second->getConn(), request->msg()
    }
    return Status::OK;
}

void GatewayServiceImpl::startServer(std::shared_ptr<ChatServer> chatServer) {
    std::thread t([chatServer]() {
        std::string server_address("0.0.0.0:50054");
        GatewayServiceImpl service(chatServer);
        ServerBuilder builder;
        builder.AddListeningPort(server_address,
                                 grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        LOG_DEBUG << "Gateway rpc Server listening on " << server_address;
        server->Wait();

    });
    t.detach();
}