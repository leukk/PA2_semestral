#pragma once
#include "InputManager.h"
#include "../utils/GameConstants.h"
#include "../utils/DataLoader.h"
#include "../scene/Scene.h"
#include <ncurses.h>
#include <cmath>
#include <chrono>
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
    bool Initialize(DataLoader& dataLoader);
    bool LoadScene(int sceneId);
    GAME_STATE GetGameState();
private:
    friend int main([[maybe_unused]] int argv, char * argc[]);
    void m_GameLoop();
    void m_InitGameWindows();
    [[nodiscard]] bool m_CheckTerminal() const;

public:
    WINDOW * gameWindow = nullptr;
    WINDOW * textWindow = nullptr;
    DataLoader gameData;
private:
    Scene * m_activeScene = nullptr;
    GAME_STATE m_gameState = SCENE_LOAD;

    int m_gameWinY = 0, m_gameWinX = 0, m_textWinY = 0;
    int m_updateRate = 0;
    int m_defaultScene = 0;

    long m_targetMs = 0; // Target execution time in ms
    long m_deltaMs = 0;  // Measured execution time in ms
    long m_waitMs = 0; // How long to wait in case execution is faster than target
};