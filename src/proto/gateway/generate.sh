protoc-23.1.0 -I ../msg -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./gateway.proto 
protoc-23.1.0 -I ../msg -I .  --cpp_out=. ./gateway.proto 