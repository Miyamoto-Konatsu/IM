#!/bin/bash

# 获取当前可执行文件的绝对路径
executable_path=$(readlink -f "$0")

# 获取当前可执行文件所在的目录（即可执行文件的上一级目录）
executable_dir=$(dirname "$executable_path")

parent_dir=$(dirname "$executable_dir")

project_dir=$(dirname "$parent_dir")
# 获取可执行文件所在目录的上一级目录

# 获取build目录的绝对路径
build_dir="$project_dir/build"

server_dir="$build_dir/src/server"

# 获取rpc服务的绝对路径
authRpcPath="$server_dir/rpc/auth/authServer"
conversationRpcPath="$server_dir/rpc/conversation/conversationServer"
msgRpcPath="$server_dir/rpc/msg/msgServer"
# 启动rpc服务
$authRpcPath &
$conversationRpcPath &
$msgRpcPath &


# 获取http服务的绝对路径
httpServerPath="$server_dir/api/api"
# 启动rpc服务后，启动http服务
$httpServerPath &


# 获取tcpserver目录的绝对路径
tcpServerPath="$server_dir/gateway/gate"
# 启动tcp服务
$tcpServerPath &

# 获取transefer目录的绝对路径
transferPath="$server_dir/transfer/transferServer"
# 启动transfer服务
$transferPath &

# 获取push目录的绝对路径
pushPath="$server_dir/push/pushServer"
# 启动push服务
$pushPath &