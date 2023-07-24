protoc-23.1.0 -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./conversation.proto
protoc-23.1.0 -I . --cpp_out=. ./conversation.proto