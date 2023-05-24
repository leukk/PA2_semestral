CC=g++
CFLAGS=-Wall -Wextra -pedantic -lncurses -g
OPT=-O0

SOURCES=main.cpp
OBJECTS=main.o
BINARY=a.out

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $(BINARY)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(BINARY) $(OBJECTS)

