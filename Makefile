LIBS=`pkg-config --libs --cflags opencv`

all:
	g++ server.cpp -o server $(LIBS) -std=c++14
	g++ client.cpp -o client $(LIBS) -std=c++14
