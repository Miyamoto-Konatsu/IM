ALL:./build/echo_server

client:./build/client

LIB = -lmuduo_net -lmuduo_base -lpthread -lmysqlclient
LIB_PATH = /usr/local/lib
INC = ./include 
ARGS = -g -Wall

src = $(wildcard *.c)
obj = $(patsubst %.c, %.o $(src))

./build/client: ./src/client/Client.cpp
	g++ $^ -o $@ -I $(INC) -L $(LIB_PATH) $(LIB) $(ARGS)

./build/echo_server: ./obj/main.o ./obj/Server.o ./obj/Service.o
	g++ $^ -o $@ -I $(INC) -L $(LIB_PATH) $(LIB) $(ARGS)

./obj/main.o : ./main.cpp 
	g++ -c $^ -o $@ -I $(INC) -L $(LIB_PATH) $(LIB) $(ARGS)
	
./obj/Server.o : ./src/server/Server.cpp
	g++ -c $< -o $@ -I $(INC) -L $(LIB_PATH) $(LIB) $(ARGS)

./obj/Service.o : ./src/server/Service.cpp
	g++ -c $< -o $@ -I $(INC) -L $(LIB_PATH) $(LIB) $(ARGS) 

./obj/UserModel.o : ./src/server/db/UserModel.cpp
	g++ -c $< -o $@ -I $(INC) -L $(LIB_PATH) $(LIB) $(ARGS) 

clean :
	rm -rf ./obj/* ./build/echo_server