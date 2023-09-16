#include "msg.h"
#include <chrono>
#include <grpcpp/support/status.h>
#include <memory>
#include <stdexcept>
#include <thread>
#include "grpcpp/server_builder.h"
#include "kafka.h"
#include "utils/msgutils.h"
#include <future>
#include "librdkafka/rdkafkacpp.h"
#include "constant.h"
using RdKafka::ErrorCode;

using grpc::ServerBuilder;
using grpc::Server;

MsgServiceImpl::MsgServiceImpl() {
    std::unique_ptr<MqProducerFactory> factory =
        std::make_unique<NewMsgMqProducerFactory>();
    producer = factory->getProducer();
}

Status MsgServiceImpl::sendMsg(ServerContext *context,
                               const sendMsgReq *request,
                               sendMsgResp *response) {
    const auto &msg = request->msg_data();

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

std::string MsgServiceImpl::getKey(const msg &request) {
    if (request.msgtype() == SINGLE_CHAT_TYPE) {
        return getSingleChatKey(request.fromuserid(), request.touserid());
    } else if (request.msgtype() == GROUP_CHAT_TYPE) {
        return getGroupChatKey(request.groupid());
    } else {
        throw std::invalid_argument("invalid msg type");
    }
}

Status MsgServiceImpl::produce(const sendMsgReq *request) {
    auto &msg = request->msg_data();
    auto requestString = request->SerializeAsString();

    auto key = getKey(msg);
    // std::promise<ErrorCode> p;
    // auto f = p.get_future();
    // std::cout << msg.fromuserid() << ' ' << msg.touserid() << std::endl;

    auto code = producer->produce(requestString, key, nullptr);
    if (code != RdKafka::ERR_NO_ERROR) {
        return Status(grpc::StatusCode::INTERNAL, "failed to push to mq");
    }
    // code = f.get();
    // if (code != RdKafka::ERR_NO_ERROR) {
    //     return Status(grpc::StatusCode::INTERNAL, "failed to push to mq");
    // }
    return Status::OK;
}

int main() {
    std::string server_address("0.0.0.0:50053");
    MsgServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "MsgServer listening on " << server_address << std::endl;
    server->Wait();
    return 0;
}