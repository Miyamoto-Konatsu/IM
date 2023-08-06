#include "user.h"
#include "protobuf/json/json.h"
#include "user.pb.h"
#include "google/protobuf/util/json_util.h"

using google::protobuf::json::MessageToJsonString;
using google::protobuf::json::JsonStringToMessage;

int main() {
    ServerRpc::user::createUserReq req;
    auto user = req.mutable_user();
    user->set_userid("test");
    user->set_nickname("test");
    user->set_password("test");
    std::string str;
    auto status = MessageToJsonString(req, &str);
    if (!status.ok()) { throw std::runtime_error("parse json error"); }
    std::cout << str << std::endl;
    return 0;
}