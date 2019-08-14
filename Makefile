LIBS=`pkg-config --libs --cflags opencv`

all:
	g++ server.cpp -o server $(LIBS) -std=c++14
	g++ client.cpp -o client $(LIBS) -std=c++14

test_socket:
	g++ test_socket.cpp -o test_socket $(LIBS) -std=c++14

.PHONY: test_socket
