#include "msg.h"
#include <chrono>
#include <grpcpp/support/status.h>
#include <memory>
#include <thread>
#include "grpcpp/server_builder.h"
#include "kafka.h"
#include "utils/msgutils.h"
#include <future>
#include "librdkafka/rdkafkacpp.h"

using RdKafka::ErrorCode;

using grpc::ServerBuilder;
using grpc::Server;

MsgServiceImpl::MsgServiceImpl() {
    std::unique_ptr<MqFactory> factory = std::make_unique<NewMsgMqFactory>();
    producer = factory->getProducer();
}

Status MsgServiceImpl::sendMsg(ServerContext *context,
                               const sendMsgReq *request,
                               sendMsgResp *response) {
    const auto &msg = request->msg();
    // std::cout << "Received message from client: " << msg.content() <<
    // std::endl; std::cout << "Received message from client id: " <<
    // msg.fromuserid()
    //           << std::endl;
    // std::cout << "Send message to client id: " << msg.touserid() <<
    // std::endl; std::cout << "Messgae type: " << msg.msgtype() << std::endl;
    // std::cout << "Sender platform: " << msg.platformid() << std::endl;

    // std::cout << "Sending response to client..." << std::endl;
    std::chrono::system_clock::time_point now =
        std::chrono::system_clock::now();
    response->set_sendtime(now.time_since_epoch().count());
    return this->produce(request);
}

Status MsgServiceImpl::produce(const sendMsgReq *request) {
    auto &msg = request->msg();
    auto msgString = msg.SerializeAsString();
    auto key = getSingleChatKey(msg.fromuserid(), msg.touserid());
    std::promise<ErrorCode> p;
    auto f = p.get_future();
    auto code = producer->produce(msgString, key, &p);
    if (code != RdKafka::ERR_NO_ERROR) {
        return Status(grpc::StatusCode::INTERNAL, "failed to push to mq");
    }
    // code = f.get();
    if (code != RdKafka::ERR_NO_ERROR) {
        return Status(grpc::StatusCode::INTERNAL, "failed to push to mq");
    }
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