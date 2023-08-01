#ifndef MSGHASNDLER_GATEWAY_H
#define MSGHASNDLER_GATEWAY_H

class GateMsgHandler {
public:
    GateMsgHandler() = default;

    GateMsgHandler(const GateMsgHandler &) = delete;

    GateMsgHandler &operator=(const GateMsgHandler &) = delete;

    ~GateMsgHandler() = default;

private:
};

#endif