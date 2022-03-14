ALL:echo_server

LIB = -lmuduo_net -lmuduo_base -lpthread
LIB_PATH = /usr/local/lib
ChatServer.o : ChatServer.cpp
    g++ $< -o $@  -L $(LIB_PATH) $(LIB)

echo_server:main.cpp 
	g++ $< -o $@  -L $(LIB_PATH) $(LIB)
