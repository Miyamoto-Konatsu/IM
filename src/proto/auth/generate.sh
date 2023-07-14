protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./auth.proto
protoc -I . --cpp_out=. ./auth.proto