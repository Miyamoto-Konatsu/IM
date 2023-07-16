#include "msg.h"
#include <chrono>
#include <thread>
#include "grpcpp/server_builder.h"

using grpc::ServerBuilder;
using grpc::Server;

Status MsgServiceImpl::sendMsg(ServerContext *context,
                               const sendMsgReq *request,
                               sendMsgResp *response) {
    const auto &msg = request->msg();
    std::cout << "Received message from client: " << msg.content() << std::endl;
    std::cout << "Received message from client id: " << msg.fromuserid()
              << std::endl;
    std::cout << "Send message to client id: " << msg.touserid() << std::endl;
    std::cout << "Messgae type: " << msg.msgtype() << std::endl;
    std::cout << "Sender platform: " << msg.platformid() << std::endl;

    std::cout << "Sending response to client..." << std::endl;
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    response->set_sendtime(now.time_since_epoch().count());

    producer.produce("test", msg.content(), msg.fromuserid());
    return Status::OK;
}

int main() {
    std::string server_address("0.0.0.0:50051");
    MsgServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}