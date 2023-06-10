COMPILER=g++
CFLAGS=-Wall -Wextra -pedantic -lncursesw -std=c++17 -g
OPT=-O0
BINARY="game.app"

UTIL_CPP=$(wildcard src/utils/*.cpp)
SCENE_CPP=$(wildcard src/scene/*.cpp)
MANAGERS_CPP=$(wildcard src/managers/*.cpp)
SCENE_OBJ_CPP=$(wildcard src/scene-objects/*.cpp)

all: $(BINARY)

$(BINARY): main.o utils.o scene.o scene-objects.o managers.o
	$(COMPILER) $(CFLAGS) $(wildcard *.o) -o $(BINARY)

main.o: src/main.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

utils.o: $(UTIL_CPP)
	$(COMPILER) $(CFLAGS) -c $^

scene.o: $(SCENE_CPP)
	$(COMPILER) $(CFLAGS) -c $^

managers.o: $(MANAGERS_CPP)
	$(COMPILER) $(CFLAGS) -c $^

scene-objects.o: $(SCENE_OBJ_CPP)
	$(COMPILER) $(CFLAGS) -c $^

clean:
	rm -rf $(BINARY) *.o

