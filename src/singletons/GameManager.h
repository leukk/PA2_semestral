#pragma once
#include "../gameconstants.h"
#include "../scene-management/Scene.h"
#include <ncurses.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

#define COMMENT_CONF_DELIM "//"
#define SCENE_CONF_DELIM "#scene"

class GameManager {
public:
    GameManager() = default;
    ~GameManager() = default;
    static GameManager& Get();

    bool Initialize(const string& gameConfig);
    void ParseMainConfig(const string& gameConfig);
    bool LoadScene(int sceneId);
    bool GameCycle(int64_t deltaMs);
    const Scene& GetActiveScene();

private:
    Scene * m_activeScene;
    vector<string> m_sceneConfigs;
public:
    WINDOW * gameWindow;
    WINDOW * textWindow;
};