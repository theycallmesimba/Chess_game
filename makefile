CC=g++
CFLAGS= -c

chessgame.o: chessgame.cpp
	$(CC) chessgame.cpp -o playchess

clean:
	rm -rf *o playchess
