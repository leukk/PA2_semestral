#include "GameManager.h"

using namespace std;
using std::chrono::high_resolution_clock, std::chrono::milliseconds, std::chrono::duration_cast;


GameManager& GameManager::Get() {
    static GameManager m_instance;
    return m_instance;
}

void GameManager::m_InitGameWindows(){
    int termSizeY = 0;
    int termSizeX = 0;
    getmaxyx(stdscr,termSizeY,termSizeX); // Retrieve size of terminal window

    int winStartY = (termSizeY / 2) - ((m_gameWinY + m_textWinY) / 2);
    int winStartX = (termSizeX / 2) - (m_gameWinX / 2);
    gameWindow = newwin(m_gameWinY, m_gameWinX, winStartY, winStartX);
    textWindow = newwin(m_textWinY, m_gameWinX, winStartY + m_gameWinY, winStartX);
}

void GameManager::m_RefreshWindows() const {
    box(gameWindow, 0, 0);
    box(textWindow, 0, 0);
    wrefresh(gameWindow);
    wrefresh(textWindow);
}

/**
 *  Checks if terminal supports all necessary features & is of required size
 *  returns true / false as result
 */
bool GameManager::m_CheckTerminal() const{
    int y,x;
    getmaxyx(stdscr,y,x); // Gets terminal y,x size
    if(y < m_gameWinY || x < m_gameWinX){
        ostringstream errorMsg;
        errorMsg << " Insufficient window size (" << y << ", " << x << ")\n";
        errorMsg << " Required minimum is (" << m_gameWinY << ", " << m_gameWinX << ")\n";
        GameManager::Get().ShowError(errorMsg.str());
        return false;
    }
    return true;
}

bool GameManager::Initialize(DataLoader* dataLoader) {
    // Set data loaded from dataLoader as gameData
    gameData = dataLoader;
    if(!gameData)
        return false;

    // Try fetch game required variables
    ostringstream missingParams;
    try {
        m_updateRate = dataLoader->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_UPDATE_RATE);
        if(!m_updateRate)
            missingParams << PARAM_UPDATE_RATE << " ";
        m_gameWinY = dataLoader->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_GAME_WIN_Y);
        if(!m_gameWinY)
            missingParams << PARAM_GAME_WIN_Y << " ";
        m_gameWinX = dataLoader->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_GAME_WIN_X);
        if(!m_gameWinX)
            missingParams << PARAM_GAME_WIN_X << " ";
        m_textWinY = dataLoader->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_TEXT_WIN_Y);
        if(!m_textWinY)
            missingParams << PARAM_TEXT_WIN_Y << " ";
        m_defaultScene = dataLoader->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_DEFAULT_SCENE);

        if(!missingParams.str().empty())
            throw invalid_argument(missingParams.str());
    }
    catch (invalid_argument& e){
        ShowError(" Missing global parameters in config\n " + string(e.what()) + "\n");
        return false;
    }
    catch (exception& e){
        ShowError(" Game initialization failed due to:\n " + string(e.what()) + "\n");
        return false;
    }

    // Set target execution time
    m_targetMs = 1000/m_updateRate;

    // Check for terminal compatibility
    if(!m_CheckTerminal())
        return false;

    // Inits ncurses game&text windows
    m_InitGameWindows();

    // Try load default scene & return result
    return LoadScene(m_defaultScene);
}

void GameManager::m_GameLoop() {
    auto startTime = high_resolution_clock::now();

    m_visualCounter = m_visualCounter < (size_t)m_updateRate ? m_visualCounter+1 : 0;

    // Clear window contents & reset text cursor position
    werase(gameWindow);
    werase(textWindow);
    wmove(textWindow,1,0);

    // Print error message if execution time takes longer than target
    if(m_waitMs < 0)
        wprintw(textWindow, " Cant keep up! Update-rate possibly set too high.\n");
    wprintw(textWindow, " Scene: %lu | Objects: %lu | Frame time: %ld-ms | Debug counter: %lu\n",
            m_deltaMs, activeSceneIndex, activeScene->sceneObjects.size(), m_visualCounter);

    // Update & render all scene objects
    double deltaS = 1000.0/(double)m_deltaMs;
    for(auto obj : activeScene->sceneObjects){
        if(!obj->active)
            continue;
        if(!obj->Update(deltaS))
            return;
        obj->Render(gameWindow, textWindow);
    }

    m_RefreshWindows();

    auto endTime = high_resolution_clock::now();

    // Get delta based on start - end time & time to wait
    m_deltaMs = duration_cast<milliseconds>(startTime - endTime).count();
    m_deltaMs = m_deltaMs == 0 ? 1 : m_deltaMs;
    m_waitMs = m_targetMs - m_deltaMs;

    // If needed nap so execution matches target
    if(m_waitMs > 0)
        napms((int)m_waitMs);
}

bool GameManager::LoadScene(int sceneIndex) {
    // Try to load scene
    Scene * newScene = nullptr;
    try {
        newScene = new Scene(sceneIndex);
        activeScene = newScene;
        activeSceneIndex = sceneIndex;
    }
    catch (exception& e){
        ShowError(" Loading scene " + to_string(sceneIndex) + " failed due to:\n" + string(e.what()) + "\n");
        return false;
    }

    // Scene successfully loaded - call Start on objects
    for (auto obj : activeScene->sceneObjects)
        obj->Start();

    return true;
}

void GameManager::ShowError(const string& message) {
    werase(gameWindow);
    werase(textWindow);

    mvwprintw(gameWindow,1,0, " Runtime error:\n%s", message.c_str());
    m_RefreshWindows();

    nodelay(gameWindow, false);
    wgetch(gameWindow);

    nodelay(gameWindow, true);
    nodelay(textWindow, true);
    nodelay(stdscr, true);

    m_RefreshWindows();
}

void GameManager::ExitGame() {
    m_gameState = EXIT;
}

GAME_STATE GameManager::GetGameState() {
    return m_gameState;
}







