COMPILER=g++
CFLAGS=-Wall -Wextra -pedantic -lncurses -std=c++17 -g
OPT=-O0


BINARY=game.app

all: $(BINARY)

$(BINARY): main.o Scene.o GameManager.o InputManager.o SceneObject.o MainMenu.o Vector2.o
	$(COMPILER) $(CFLAGS) $^ -o $(BINARY)

main.o: src/main.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

GameManager.o: src/singletons/GameManager.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

InputManager.o: src/singletons/InputManager.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

Scene.o: src/scene/Scene.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

SceneObject.o: src/scene/SceneObject.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

MainMenu.o: src/scene-objects/MainMenu.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

Vector2.o: src/utils/Vec2.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(BINARY) *.o

