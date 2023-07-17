protoc-23.1.0 -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./auth.proto
protoc-23.1.0 -I . --cpp_out=. ./auth.proto