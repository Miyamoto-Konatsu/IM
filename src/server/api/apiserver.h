#ifndef APISERVER_API_H
#define APISERVER_API_H

#include "httplib.h"

#include <iostream>
#include <map>
// using namespace httplib;
using HttpRequest = httplib::Request;
using HttpResponse = httplib::Response;

class ApiServer : public std::enable_shared_from_this<ApiServer> {
public:
    ApiServer(unsigned short port, int numThreads);
    ~ApiServer();
    void start();
    //  void onRequest(const HttpRequest &req, HttpResponse *resp);
    void resigterApi(const std::string &path, const std::string &method,
                     const std::function<void(const HttpRequest &,
                                              HttpResponse &)> &callback);

private:
    std::map<std::pair<std::string, std::string>,
             std::function<void(const HttpRequest &, HttpResponse &)>>
        apiMap_;
    int numThreads_;
    unsigned short port_;
    std::shared_ptr<httplib::Server> server_;
};

#endif