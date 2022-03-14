ALL:echo_server

LIB = -lmuduo_net -lmuduo_base -lpthread
LIB_PATH = /usr/local/lib
INC = ./include

echo_server: ./obj/main.o ./obj/Server.o
	g++ $^ -o $@ -I $(INC) -L $(LIB_PATH) $(LIB)

./obj/main.o : ./main.cpp 
	g++ -c $^ -o $@ -I $(INC) -L $(LIB_PATH) $(LIB)
	
./obj/Server.o : ./src/Server.cpp
	g++ -c $< -o $@ -I $(INC) -L $(LIB_PATH) $(LIB)

clean :
	rm -rf ./obj/* echo_server