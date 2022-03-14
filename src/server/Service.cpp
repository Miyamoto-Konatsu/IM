#include "server/Service.h"
using namespace std;
using namespace muduo;
using namespace muduo::net;

void Service::register(const TcpConnectionPtr& conn, const nlohmann::json msg, Timestamp time) {
    muduo::string nickname = msg["nickname"];
    muduo::string password = msg["password"];
    
}