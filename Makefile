COMPILER=g++
CFLAGS=-Wall -Wextra -pedantic -lncurses -std=c++17 -g
OPT=-O0


BINARY=game.app

all: $(BINARY)

$(BINARY): main.o GameManager.o Scene.o
	$(COMPILER) $(CFLAGS) $^ -o $(BINARY)

main.o: src/main.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

GameManager.o: src/singletons/GameManager.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

Scene.o: src/scene-management/Scene.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(BINARY) *.o

