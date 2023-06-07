#include "GameManager.h"

using namespace std;

GameManager& GameManager::Get() {
    static GameManager m_instance;
    return m_instance;
}

void GameManager::ParseMainConfig(const string &configPath) {
    // Open config file
    ifstream configStream(configPath);

    // Split config into m_sceneConfigs vector
    string line;
    ostringstream sceneConfigBuffer;
    bool first = true;
    while (configStream.good()){
        getline(configStream, line);

        // Skip if line is a comment (starts with CFG_COMMENT_ID) or empty
        if(line.rfind(COMMENT_CONF_DELIM, 0) || line.empty())
            continue;

        // Detect new scene config (starts with CFG_SCENE_ID)
        // Push loaded scene config to m_sceneConfigs vector
        if(line.rfind(SCENE_CONF_DELIM, 0) != string::npos && !first){
            m_sceneConfigs.push_back(sceneConfigBuffer.str());
            sceneConfigBuffer.clear();
        }

        // Copy other config lines to sceneConfigBuffer
        sceneConfigBuffer << line;
        first = false;
    }

    printw("Loaded config from: %s\n", configPath.c_str());
    napms(500);
}

bool GameManager::Initialize(const string &configPath) {
    int termSizeY = 0;
    int termSizeX = 0;
    getmaxyx(stdscr,termSizeY,termSizeX); // Retrieve size of terminal window

    int winStartY = (termSizeY / 2) - ((GAME_WIN_Y + TEXT_WIN_Y) / 2);
    int winStartX = (termSizeX / 2) - (GAME_WIN_X / 2);
    gameWindow = newwin(GAME_WIN_Y, GAME_WIN_X, winStartY, winStartX);
    textWindow = newwin(TEXT_WIN_Y, GAME_WIN_X, winStartY + GAME_WIN_Y, winStartX);

    box(gameWindow,0,0);
    wrefresh(gameWindow);
    box(textWindow,0,0);
    wrefresh(textWindow);

    getch();

    ParseMainConfig(configPath); // Parse main config from file at configPath
    //if(!LoadScene(0)) // Try load first scene
    //    return false;
    return true;
}

bool GameManager::GameCycle(int64_t deltaMs) {
    return false;
}

bool GameManager::LoadScene(int sceneId) {
    // Config for scene with given id does not exist
    if(m_sceneConfigs[sceneId].empty())
        return false;

    // Delete current scene
    if(m_activeScene)
        delete m_activeScene;

    // Create new scene & initialize from scene config
    m_activeScene = new Scene();
    if(!m_activeScene || !m_activeScene->Initialize(m_sceneConfigs[sceneId]))
        return false;

    return true;
}

const Scene& GameManager::GetActiveScene() {
    return *m_activeScene;
}



