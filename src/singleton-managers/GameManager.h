#pragma once
#include "../scene-base/Scene.h"
#include "../utils/DataLoader.h"
#include "../utils/GameConstants.h"
#include "InputManager.h"
#include <ncurses.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class Scene;
class DataLoader;

using std::max;
using std::vector;
using std::chrono::high_resolution_clock, std::chrono::milliseconds, std::chrono::duration_cast;

/**
 * Game state enum
 */
enum GAME_STATE{
    SCENE_LOAD,
    RUNNING,
    EXIT
};

/**
 * Game management singleton.
 *
 * Controls game flow such as: object updates, rendering, game dependencies initialization
 * @note Cannot be retrieved, has static interface for interaction. (except from main)
 */
class GameManager {
private:
    GameManager() = default;
public:
    GameManager(const GameManager& other) = delete;
    ~GameManager();

    /**
     * Currently active scene index
     * @return index of currently active scene
     */
    static int GetActiveSceneIndex();
    /**
     * Currently active scene pointer
     * @return currently active scene pointer
     */
    static Scene* GetActiveScene();
    /**
     * Game data reference getter
     * @return game data reference
     */
    static DataLoader& GetGameData();
    /**
     * Text window pointer getter
     * @return text window pointer
     */
    static WINDOW* GetTextWindow();
    /**
     * Game window pointer getter
     * @return game win pointer
     */
    static WINDOW* GetGameWindow();
    /**
     * Game state getter
     * @return current game state
     */
    static GAME_STATE GetGameState();
    /**
     * Menu scene index getter
     * @return menu scene index
     */
    static int GetMenuSceneIndex();
    /**
     * Hub scene index getter
     * @return hub scene index
     */
    static int GetHubSceneIndex();

    /**
     * Loads scene of provided sceneIndex and updates activeSceneIndex variable.
     *
     * Tries loading scene first, if loading fails
     * shows loading error & retrieves to previous scene.
     * Else deletes currently active scene and replaces it
     * with newly loaded one.
     * @param sceneIndex
     * @return loading success
     */
    static bool LoadScene(int sceneIndex);
    /**
     * Shows user error message.
     *
     * Pauses game execution and shows user error message.
     * @param message error message
     */
    static void ShowError(const string& message);
    /**
     * Exits game.
     *
     * Sets game state to exit which results in
     * termination during next update.
     */
    static void ExitGame();
    /**
     * Refreshes game/text windows.
     *
     * Refreshes both text and game windows and adds
     * box outline to both.
     */
    static void RefreshWindows();

private:
    /**
     * Game manager singleton getter.
     * @return game manager reference
     */
    static GameManager& m_Get();
    friend int main([[maybe_unused]] int argv, char * argc[]);
    /**
     * Initializes game manager.
     *
     * Initializes all game manager dependencies including:
     * terminal, game/text windows, config data and player data.
     * Loads config defined main menu scene afterwards.
     * @param gameConfigPath game config path provided by program arguments
     * @return initialization success
     */
    bool m_Initialize(char * gameConfigPath);
    /**
     * Main game loop.
     *
     * Updates and renders all active sceneObjects contained within currently active scene.
     * Measures execution time & naps / warns to match target execution time.
     */
    void m_GameLoop();
    /**
     * Initializes game windows.
     *
     * Initializes gameWindow and textWindow variables,
     * starts color mode and initializes color pairs.
     */
    void m_InitGameWindows();
    /**
     * Checks for terminal compatibility.
     *
     * Returns true if terminal is of required size by config
     * and supports color.
     * @return terminal supported
     */
    [[nodiscard]] bool m_CheckTerminal() const;

private:
    GAME_STATE m_gameState = SCENE_LOAD; /// Game manager state
    WINDOW * m_gameWindow = stdscr; /// Main game window
    WINDOW * m_textWindow = stdscr; /// Text window
    DataLoader * m_gameData = nullptr; /// Game data pointer

    Scene * m_activeScene = nullptr; /// Currently active scene pointer
    int m_activeSceneIndex = 0; /// Currently active scene

    int m_gameWinY = 0, m_gameWinX = 0, m_textWinY = 0; /// Game & text window y/x size, text window uses same x size as game window
    int m_updateRate = 0; /// Game update rate (times/second)
    int m_hubSceneIndex = 0, m_menuSceneIndex = 0; /// Default hub/scene indexes

    long m_targetMs = 0; /// Target execution time in ms
    long m_deltaMs = 0;  /// Measured execution time in ms
    long m_waitMs = 0; /// How long to wait in case execution is faster than m_target

    size_t m_visualCounter = 0; /// Debug counter
};