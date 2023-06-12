COMPILER=g++
CFLAGS=-lncursesw -std=c++17
OPT=-O0
BINARY="game.app"

UTIL_CPP=$(wildcard src/utils/*.cpp)
SCENE_CPP=$(wildcard src/scene/*.cpp)
MANAGERS_CPP=$(wildcard src/managers/*.cpp)
SCENE_OBJ_CPP=$(wildcard src/scene-objects/*.cpp)

OBJ_DIR="/obj"

all: $(BINARY)
	rm *.o

compile: $(BINARY)
	rm *.o
	mv $(BINARY) $(USER)

run: $(BINARY)
	rm *.o
	./$(BINARY) examples/1/main.cfg

doc:
	doxygen Doxyfile

clean:
	rm $(BINARY) *.o $(USER) *.app

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

