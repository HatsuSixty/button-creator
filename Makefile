PKGS=raylib glfw3
CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb `pkg-config --cflags $(PKGS)`
LIBS=`pkg-config --libs $(PKGS)` -lm

button-creator: main.o
	$(CC) $(CFLAGS) -o button-creator main.o $(LIBS)

main.o: main.c config.h
	$(CC) $(CFLAGS) -o main.o -c main.c $(LIBS)