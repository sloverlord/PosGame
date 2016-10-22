CC=clang++
CFLAGS=-Wall -g

BINS= game

all: $(BINS)

game: game.cpp game.h movement.cpp
	$(CC) $(CFLAGS) -o game game.cpp

wrap:
	tar cvzf game.tgz game.cpp Makefile game.h movement.cpp

clean:
	rm game
