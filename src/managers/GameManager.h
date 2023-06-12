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
class DataLoader;

using std::vector;

enum GAME_STATE{
    SCENE_LOAD,
    RUNNING,
    EXIT
};

class GameManager {
private:
    GameManager() = default;
public:
    GameManager(const GameManager& other) = delete;
    ~GameManager() = default;

    static int GetActiveSceneIndex();
    static Scene* GetActiveScene();
    static DataLoader& GetGameData();
    static WINDOW* GetTextWindow();
    static WINDOW* GetGameWindow();
    static GAME_STATE GetGameState();
    static int GetMenuSceneIndex();
    static int GetHubSceneIndex();

    static bool LoadScene(int sceneIndex);
    static void ShowError(const string& message);
    static void ExitGame();
    static void RefreshWindows();

private:
    static GameManager& m_Get();
    friend int main([[maybe_unused]] int argv, char * argc[]);
    bool m_Initialize(DataLoader* dataLoader);
    void m_GameLoop();
    void m_InitGameWindows();
    [[nodiscard]] bool m_CheckTerminal() const;

private:
    GAME_STATE m_gameState = SCENE_LOAD;
    WINDOW * m_gameWindow = stdscr;
    WINDOW * m_textWindow = stdscr;
    DataLoader * m_gameData = nullptr;

    Scene * m_activeScene = nullptr;
    int m_activeSceneIndex = 0;

    int m_gameWinY = 0, m_gameWinX = 0, m_textWinY = 0;
    int m_updateRate = 0;
    int m_hubSceneIndex = 0, m_menuSceneIndex = 0;

    long m_targetMs = 0; // Target execution time in ms
    long m_deltaMs = 0;  // Measured execution time in ms
    long m_waitMs = 0; // How long to wait in case execution is faster than m_target

    size_t m_visualCounter = 0;
};