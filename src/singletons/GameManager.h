#pragma once
#include "../GameConstants.h"
#include "../scene-management/Scene.h"
#include <ncurses.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>



class GameManager {
public:
    GameManager() = default;
    ~GameManager() = default;
    static GameManager& Get();

    bool Initialize(const string& gameConfig);

    bool LoadScene(int sceneId);
    bool GameCycle(int64_t deltaMs);
    const Scene& GetActiveScene();
private:
    void m_InitGameWindows();
    void m_ParseMainConfig(const string& gameConfig);

private:
    Scene * m_activeScene;
    vector<string> m_sceneConfigs;
public:
    WINDOW * gameWindow;
    WINDOW * textWindow;
};