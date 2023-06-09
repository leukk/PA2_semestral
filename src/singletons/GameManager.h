#pragma once
#include "InputManager.h"
#include "../utils/GameConstants.h"
#include "../scene/Scene.h"
#include <ncurses.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class Scene;

using std::vector;

enum GAME_STATE{
    SCENE_LOAD,
    RUNNING,
    EXIT,
    CRASH
};

class GameManager {
private:
    GameManager() = default;
public:
    GameManager(const GameManager& other) = delete;
    ~GameManager() = default;

    static GameManager& Get();
    bool LoadScene(int sceneId);
    const Scene& GetActiveScene();
    GAME_STATE GetGameState();
private:
    friend int main([[maybe_unused]] int argv, char * argc[]);
    bool m_Initialize(const string& gameConfig);
    bool m_UpdateGame(int64_t deltaMs);
    void m_InitGameWindows();
    void m_ParseMainConfig(const string& gameConfig);

public:
    WINDOW * gameWindow = nullptr;
    WINDOW * textWindow = nullptr;
private:
    Scene * m_activeScene = nullptr;
    vector<string> m_sceneConfigs;
    GAME_STATE m_gameState = SCENE_LOAD;
};