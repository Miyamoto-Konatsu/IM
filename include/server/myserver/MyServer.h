#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H
#include "server/myserver/Common.h"
#include "server/myserver/Connection.h"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

class MyServer {
    typedef int *pipe_type_ptr;
    typedef int pipe_type;
    friend class Connection;

  public:
    void Init(const char *ip = "127.0.0.1", const char *port = "6000") {
        InitEpoll(ip, port);
        InitPipe();
        InitWorker();
    }

    void Start() {
        while (true) {
            int ready_count =
                epoll_wait(epoll_fd_, events_.data(), events_.size(), 5000);
            for (int i = 0; i < ready_count; ++i) {
                int ready_fd = events_[i].data.fd;
                if (ready_fd == listen_fd_) {
                    sockaddr_in client_sockeraddr;
                    socklen_t clientlen;
                    int client_fd = accept(
                        listen_fd_, (sockaddr *)&client_sockeraddr, &clientlen);
                    SetNonBlocking(client_fd);
                    write(pipes[round_][1], &client_fd, sizeof client_fd);
                    round_ = (round_ + 1) % worker_number_;
                }
            }
        }
        close(listen_fd_);
    }

    void SetMessageCallback(const MessageCallback &mc) {
        message_callback = mc;
    }
    void SetConnectionCallback(const ConnectionCallback &cc) {
        connection_callback = cc;
    }

  private:
    void InitEpoll(const char *ip = "127.0.0.1", const char *port = "6000") {
        listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in sa;
        memset(&sa, 0, sizeof(sa));
        sa.sin_family = AF_INET;
        sa.sin_port = htons(atoi(port));
        sa.sin_addr.s_addr = inet_addr(ip);
        if (bind(listen_fd_, (const sockaddr *)&sa, sizeof(struct sockaddr))) {
            cout << "bind failed" << endl;
            exit(0);
        }
        listen(listen_fd_, 1024);
        epoll_fd_ = epoll_create(1);
        epoll_event ep_event;
        ep_event.events = EPOLLIN | EPOLLERR;
        ep_event.data.fd = listen_fd_;
        epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, listen_fd_, &ep_event);
        events_.resize(8);
    }
    
    void InitPipe() {
        for (int i = 0; i < worker_number_; ++i) {
            pipe_type_ptr ptr = new pipe_type(2);
            if (pipe(ptr) == -1) {
                throw exception();
            }
            pipes.push_back(ptr);
        }
    }

    void InitWorker() {
        for (int i = 0; i < worker_number_; ++i) {
            works.push_back(thread(&MyServer::Worker, this, i));
        }
    }

    void Close(int fd, int epoll_fd) {
        Epoll_Del(fd, EPOLLIN | EPOLLERR, epoll_fd);
        close(fd);
    }

    void Worker(int worker_id) {
        vector<struct epoll_event> events(4096);
        unordered_map<int, shared_ptr<Connection>> fd2conn;
        int epoll_fd = epoll_create(1);
        int pipe_fd = pipes[worker_id][0];
        Epoll_Add(pipe_fd, EPOLLIN | EPOLLERR, epoll_fd);
        while (true) {
            int ready_count =
                epoll_wait(epoll_fd, events.data(), events.size(), 5000);
            for (int i = 0; i < ready_count; ++i) {
                int ready_fd = events[i].data.fd;
                //主线程发来新的连接
                if (ready_fd == pipe_fd) {
                    debug_message(to_string(worker_id));
                    debug_message("new connection");
                    int client_fd;
                    if (read(pipe_fd, &client_fd, sizeof client_fd) <= 0)
                        continue;
                    Epoll_Add(client_fd, EPOLLIN | EPOLLERR, epoll_fd);
                    fd2conn[client_fd] =
                        make_shared<Connection>(this, client_fd);
                    connection_callback(fd2conn[client_fd].get());
                } else {
                    auto &conn = fd2conn[ready_fd];
                    if (events[i].events & EPOLLIN) {
                        try {
                            conn->Read();
                        } catch (const exception &e) {
                            fd2conn.erase(ready_fd);
                            Close(ready_fd, epoll_fd);
                        } catch (...) {
                            fd2conn.erase(ready_fd);
                            Close(ready_fd, epoll_fd);
                        }
                    } else {
                        fd2conn.erase(ready_fd);
                        Close(ready_fd, epoll_fd);
                    }
                }
            }
        }
    }

    void Epoll_Add(int fd, uint32_t events, int epoll_fd = -1) {
        if (-1 == epoll_fd)
            epoll_fd = epoll_fd_;
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = fd;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
            perror("epoll_ctl");
            exit(-1);
        }
    }

    void Epoll_Del(int fd, uint32_t events, int epoll_fd = -1) {
        if (-1 == epoll_fd)
            epoll_fd = epoll_fd_;
        struct epoll_event ev;
        ev.events = events;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev) == -1) {
            perror("epoll_ctl");
            exit(-1);
        }
    }

    vector<struct epoll_event> events_;
    int listen_fd_;
    int epoll_fd_;
    int round_ = 0;
    int worker_number_ = 4;
    vector<pipe_type_ptr> pipes;
    vector<thread> works;
    MessageCallback message_callback;
    ConnectionCallback connection_callback;
};

#endif