MAIN=main
LIBS=`pkg-config --libs --cflags opencv`

all:
	g++ $(MAIN).cpp -o $(MAIN) $(LIBS)
