COMPILER=g++
LFLAGS_DEV=-L /usr/local/ncurses/6_4/lib/lib* -lncursesw
LFLAGS=-lncursesw
CFLAGS=-O2 -std=c++17 -Wall -pedantic -g

BINARY=game.app
BINARY_CONFIG=examples/1/main.cfg
LOGIN=kalmakri

SRC_DIR=src
OBJ_DIR=obj
SRCS=$(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
SRC_NAMES=$(patsubst %.cpp, %,$(notdir $(SRCS)))

all: $(SRC_NAMES)
	$(COMPILER) $(wildcard $(OBJ_DIR)/*) $(CFLAGS) $(LFLAGS) -o $(BINARY)

dev: $(SRC_NAMES)
	$(COMPILER) $(wildcard $(OBJ_DIR)/*) $(CFLAGS) $(LFLAGS_DEV) -o $(BINARY)

compile: all
	mv $(BINARY) $(LOGIN)

run: all
	./$(BINARY) $(BINARY_CONFIG)

doc:
	doxygen Doxyfile

clean:
	rm -rf $(BINARY) $(LOGIN) $(OBJ_DIR) doc

$(SRC_NAMES): $(OBJ_DIR)
	$(COMPILER) $(wildcard $(SRC_DIR)/$(@).cpp $(SRC_DIR)/**/$(@).cpp) $(CFLAGS) -c -o $(OBJ_DIR)/$(@).o

$(OBJ_DIR):
	mkdir -p $(@)





