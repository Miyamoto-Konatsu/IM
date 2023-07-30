#include "conversation.h"
#include "constant.h"
#include "conversation.pb.h"
#include "utils/msgutils.h"

int main() {
    ConversationClient client(grpc::CreateChannel(
        "localhost:50051", grpc::InsecureChannelCredentials()));
    // setConversationReq req;
    // setConversationResp resp;
    // RpcConversationData *converation = new RpcConversationData;
    // converation->set_conversationid(getConversationIdForSingle("123",
    // "321")); converation->set_ownerid("123");
    // converation->set_conversationtype(SINGLE_CHAT_TYPE);
    // converation->set_touserid("321");
    // // converation->set_maxseq(0);
    // // converation->set_minseq(0);
    // // converation->set_groupid("");

    // req.set_allocated_conversation(converation);

    // auto status = client.setConversation(&req, &resp);
    // if (status.ok()) {
    //     std::cout << "setConversation success" << std::endl;
    // } else {
    //     std::cout << "setConversation failed" << std::endl;
    // }

    // getConversationResp getConversationResp;
    // getConversationReq getConversationReq;
    // getConversationReq.set_owneruserid("123");
    // getConversationReq.set_conversationid(
    //     getConversationIdForSingle("123", "321"));
    // auto status =
    //     client.getConversation(&getConversationReq, &getConversationResp);
    // if (status.ok()) {
    //     std::cout << "getConversation success" << std::endl;
    //     std::cout << "conversationId: "
    //               << getConversationResp.conversation().conversationid()
    //               << std::endl;
    //     std::cout << "ownerId: " << getConversationResp.conversation().ownerid()
    //               << std::endl;
    //     std::cout << "toUserId: "
    //               << getConversationResp.conversation().touserid() << std::endl;
    //     std::cout << "conversationType: "
    //               << getConversationResp.conversation().conversationtype()
    //               << std::endl;
    //     std::cout << "maxSeq: " << getConversationResp.conversation().maxseq()
    //               << std::endl;
    //     std::cout << "minSeq: " << getConversationResp.conversation().minseq()
    //               << std::endl;
    //     std::cout << "groupId: " << getConversationResp.conversation().groupid()
    //               << std::endl;
    // } else {
    //     std::cout << "getConversation failed" << std::endl;
    // }

    // getAllConversationsResp allConversationsResp;
    // getAllConversationsReq allConversationsReq;
    // allConversationsReq.set_owneruserid("123");
    // status =
    //     client.getAllConversations(&allConversationsReq, &allConversationsResp);
    // if (status.ok()) {
    //     std::cout << "getAllConversations success" << std::endl;
    //     for (auto &item : allConversationsResp.conversations()) {
    //         std::cout << "conversationId: " << item.conversationid()
    //                   << std::endl;
    //         std::cout << "ownerId: " << item.ownerid() << std::endl;
    //         std::cout << "toUserId: " << item.touserid() << std::endl;
    //         std::cout << "conversationType: " << item.conversationtype()
    //                   << std::endl;
    //         std::cout << "maxSeq: " << item.maxseq() << std::endl;
    //         std::cout << "minSeq: " << item.minseq() << std::endl;
    //         std::cout << "groupId: " << item.groupid() << std::endl;
    //     }
    // } else {
    //     std::cout << "getAllConversations failed" << std::endl;
    // }

    // getConversationIDsResp conversationIDsResp;
    // getConversationIDsReq conversationIDsReq;
    // conversationIDsReq.set_userid("123");
    // status =
    //     client.getConversationIDs(&conversationIDsReq, &conversationIDsResp);
    // if (status.ok()) {
    //     std::cout << "getConversationIDs success" << std::endl;
    //     for (auto &item : conversationIDsResp.conversationids()) {
    //         std::cout << "conversationId: " << item << std::endl;
    //     }
    // } else {
    //     std::cout << "getConversationIDs failed" << std::endl;
    // }

    // getUserConversationIDsHashResp userConversationIDsHashResp;
    // getUserConversationIDsHashReq userConversationIDsHashReq;
    // userConversationIDsHashReq.set_owneruserid("123");
    // status = client.getUserConversationIDsHash(&userConversationIDsHashReq,
    //                                            &userConversationIDsHashResp);
    // if (status.ok()) {
    //     std::cout << "getUserConversationIDsHash success" << std::endl;
    //     std::cout << "hash: " << userConversationIDsHashResp.hash()
    //               << std::endl;
    // } else {
    //     std::cout << "getUserConversationIDsHash failed" << std::endl;
    // }

    createSingleChatConversationsResp createSingleChatConversationsResp;
    createSingleChatConversationsReq createSingleChatConversationsReq;
    createSingleChatConversationsReq.set_sendid("123");
    createSingleChatConversationsReq.set_recvid("321");
   auto status = client.createSingleChatConversations(
        &createSingleChatConversationsReq, &createSingleChatConversationsResp);
    if (status.ok()) {
        std::cout << "createSingleChatConversations success" << std::endl;
    
    } else {
        std::cout << "createSingleChatConversations failed" << std::endl;
        std::cout << status.error_code() << std::endl;
        std::cout << status.error_message() << std::endl;
    }
    return 0;
}
