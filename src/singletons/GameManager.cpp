#include "GameManager.h"

using namespace std;

GameManager& GameManager::Get() {
    static GameManager m_instance;
    return m_instance;
}

void GameManager::m_ParseMainConfig(const string &configPath) {
    // Open config file
    ifstream configStream(configPath);

    // Split config into m_sceneConfigs vector
    string line;
    ostringstream sceneConfigBuffer;
    bool first = true;
    while (configStream.good()){
        getline(configStream, line);

        // Remove line comments (text following comment delimiter)
        size_t commentPos = line.find(CONF_COMMENT_DELIM);
        if(commentPos != string::npos)
            line = line.substr(0,commentPos);

        // Skip if line is empty
        if(line.empty())
            continue;

        // Detect new scene config (starts with scene delimiter)
        // Push loaded scene config to m_sceneConfigs vector
        bool newScene = line.rfind(CONF_SCENE_DELIM, 0) != string::npos;
        if(newScene && !first){
            m_sceneConfigs.push_back(sceneConfigBuffer.str());
            sceneConfigBuffer.clear();
        }

        if(newScene)
            continue;

        // Copy other config lines to sceneConfigBuffer
        sceneConfigBuffer << line << " ";
        first = false;
    }
    // Push last scene to scene config vector
    m_sceneConfigs.push_back(sceneConfigBuffer.str());

    printw("Loaded %zu scenes\n", m_sceneConfigs.size());

    if(m_sceneConfigs.empty())
        throw std::logic_error("Scene config invalid, no scenes found\n");
}

void GameManager::m_InitGameWindows(){
    int termSizeY = 0;
    int termSizeX = 0;
    getmaxyx(stdscr,termSizeY,termSizeX); // Retrieve size of terminal window

    int winStartY = (termSizeY / 2) - ((GAME_WIN_Y + TEXT_WIN_Y) / 2);
    int winStartX = (termSizeX / 2) - (GAME_WIN_X / 2);
    gameWindow = newwin(GAME_WIN_Y, GAME_WIN_X, winStartY, winStartX);
    textWindow = newwin(TEXT_WIN_Y, GAME_WIN_X, winStartY + GAME_WIN_Y, winStartX);
}

bool GameManager::Initialize(const string &configPath) {
    try {
        m_InitGameWindows(); // Inits ncurses windows
        m_ParseMainConfig(configPath); // Parse main config from file at configPath
    }
    catch (exception& e){
        printw("Game initialization failed due to:\n%s", e.what());
    }

    if(!LoadScene(0)) // Try load first scene
        return false;
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
    delete m_activeScene;

    // Create new scene
    m_activeScene = new Scene();
    if(!m_activeScene)
        return false;

    // Try to initialize scene
    try {
        m_activeScene->Initialize(m_sceneConfigs[sceneId]);
    }
    catch (exception& e){
        printw("Loading scene %d failed due to:\n%s", sceneId, e.what());
    }

    return true;
}

const Scene& GameManager::GetActiveScene() {
    return *m_activeScene;
}



