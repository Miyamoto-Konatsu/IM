#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

enum class MsgType {
    sign_in = 0,
    sign_in_res,
    sign_up,
    sign_up_res,
    sign_out,
    chat_send,
    chat_recv,
    add_friend,
    add_friend_res,
    create_group,
    create_group_res,
    join_in_group,
    join_in_group_res,
    query_group,
    query_group_res,
    new_group_user
};

#endif