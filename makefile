CC = g++

OBJS = tictactoe-v1.0.cpp header.hpp

main: $(OBJS)
	$(CC) -o main $(OBJS)

main.o: tictactoe-v1.0.cpp