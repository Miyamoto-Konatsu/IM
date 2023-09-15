#ifndef CLIENTMAP_GATEWAY_H
#define CLIENTMAP_GATEWAY_H

#include "client.h"
#include "muduo/net/Callbacks.h"
#include "unordered_map"
#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include <muduo/base/Singleton.h>

using std::vector;
using ClientPtr = std::shared_ptr<Client>;
using std::mutex;
using std::unordered_map;

class ClientMap {
public:
    void insert(const ClientPtr &client) {
        std::lock_guard<mutex> lock(mutex_);
        clients_[client->getClinetId()].push_back(client);
        connToClient_[client->getConn()] = client;
    }

    void erase(const muduo::net::TcpConnectionPtr &conn) {
        std::lock_guard<mutex> lock(mutex_);
        auto it = connToClient_.find(conn);
        if(it == connToClient_.end()) { return; }
        auto client = it->second;
                
        if (client != nullptr) {
            auto &clients = clients_[client->getClinetId()];
            for (auto it = clients.begin(); it != clients.end(); ++it) {
                if (*it == client) {
                    clients.erase(it);
                    break;
                }
            }
            connToClient_.erase(conn);
        }
    }

    vector<ClientPtr> find(const std::string &id) {
        std::lock_guard<mutex> lock(mutex_);
        auto it = clients_.find(id);
        if (it != clients_.end()) { return it->second; }
        return vector<ClientPtr>();
    }

    ClientPtr find(const muduo::net::TcpConnectionPtr &conn) {
        std::lock_guard<mutex> lock(mutex_);
        auto it = connToClient_.find(conn);
        if (it != connToClient_.end()) { return it->second; }
        return nullptr;
    }

    void clear() {
        std::lock_guard<mutex> lock(mutex_);
        clients_.clear();
        connToClient_.clear();
    }

    unordered_map<std::string, vector<ClientPtr>> getAll() {
        std::lock_guard<mutex> lock(mutex_);
        return clients_;
    }

private:
    mutex mutex_;
    unordered_map<std::string, vector<ClientPtr>> clients_;
    unordered_map<muduo::net::TcpConnectionPtr, ClientPtr> connToClient_;
};
#endif