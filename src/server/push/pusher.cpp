#include "pusher.h"

Pusher::Pusher() {
}

Pusher::~Pusher() {
}

bool Pusher::pushMsg2User(const msg &msg) {
    std::cout << msg.fromuserid() << ' ' << msg.touserid() << ' '
              << msg.content() << std::endl;
    return true;
}

bool Pusher::pushMsg2Group(const msg &msg) {
    std::cout << msg.fromuserid() << ' ' << msg.groupid() << ' '
              << msg.content() << std::endl;
    return true;
}