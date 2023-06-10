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

/**
 *  Checks if terminal supports all necessary features & is of required size
 *  returns true / false as result
 */
bool GameManager::m_CheckTerminal() const{
    int y,x;
    getmaxyx(stdscr,y,x); // Gets terminal y,x size
    if(y < m_gameWinY || x < m_gameWinX){
        printw(" Insufficient window size (%d,%d)\n", y, x);
        printw(" Required minimum is (%d,%d)\n",m_gameWinY, m_gameWinX);
        refresh();
        return false;
    }
    return true;
}

bool GameManager::Initialize(DataLoader& dataLoader) {
    // Set data loaded from dataLoader as gameData
    gameData = dataLoader;

    // Try fetch game required variables
    ostringstream missingParams;
    try {
        m_updateRate = dataLoader.ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_UPDATE_RATE);
        if(!m_updateRate)
            missingParams << PARAM_UPDATE_RATE << " ";
        m_gameWinY = dataLoader.ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_GAME_WIN_Y);
        if(!m_gameWinY)
            missingParams << PARAM_GAME_WIN_Y << " ";
        m_gameWinX = dataLoader.ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_GAME_WIN_X);
        if(!m_gameWinX)
            missingParams << PARAM_GAME_WIN_X << " ";
        m_textWinY = dataLoader.ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_TEXT_WIN_Y);
        if(!m_textWinY)
            missingParams << PARAM_TEXT_WIN_Y << " ";
        m_defaultScene = dataLoader.ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_DEFAULT_SCENE);

        if(!missingParams.str().empty())
            throw invalid_argument(missingParams.str());
    }
    catch (invalid_argument& e){
        printw(" Missing global parameters in config\n%s\n",e.what());
        refresh();
        return false;
    }
    catch (exception& e){
        printw(" Game initialization failed due to:\n%s", e.what());
        refresh();
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

    // Clear window contents & reset text cursor position
    werase(gameWindow);
    werase(textWindow);
    wmove(textWindow,1,0);

    // Print error message if execution time takes longer than target
    if(m_waitMs < 0)
        wprintw(textWindow, " Cant keep up! Update-rate possibly set too high.\n");
    wprintw(textWindow, " Frame time: %ld ms\n", m_deltaMs);

    // Update & render all scene objects
    double deltaS = 1000.0/(double)m_deltaMs;
    for(auto obj : m_activeScene->sceneObjects){
        obj->Update(deltaS);
        obj->Render(gameWindow, textWindow);
    }

    // Create box outline around windows
    box(gameWindow,0,0);
    box(textWindow,0,0);

    // Refresh game/text windows
    wrefresh(gameWindow);
    wrefresh(textWindow);

    auto endTime = high_resolution_clock::now();

    // Get delta based on start - end time & time to wait
    m_deltaMs = duration_cast<milliseconds>(startTime - endTime).count();
    m_deltaMs = m_deltaMs == 0 ? 1 : m_deltaMs;
    m_waitMs = m_targetMs - m_deltaMs;

    // If needed nap so execution matches target
    if(m_waitMs > 0)
        napms((int)m_waitMs);
}

bool GameManager::LoadScene(int sceneId) {
    // Delete current scene
    delete m_activeScene;

    // Try to initialize scene
    try {
        m_activeScene = new Scene(sceneId);
    }
    catch (exception& e){
        printw(" Loading scene %d failed due to:\n%s\n", sceneId, e.what());
        return false;
    }

    return true;
}

GAME_STATE GameManager::GetGameState() {
    return m_gameState;
}



