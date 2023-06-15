#include "GameManager.h"

GameManager::~GameManager() {
    delete m_activeScene;
    delete m_gameData;
}

GameManager& GameManager::m_Get() {
    static GameManager m_instance;
    return m_instance;
}

GAME_STATE GameManager::GetGameState() {
    GameManager& gm = GameManager::m_Get();
    return gm.m_gameState;
}

int GameManager::GetActiveSceneIndex() {
    GameManager& gm = GameManager::m_Get();
    return gm.m_activeSceneIndex;
}

int GameManager::GetMenuSceneIndex() {
    GameManager& gm = GameManager::m_Get();
    return gm.m_menuSceneIndex;
}

int GameManager::GetHubSceneIndex() {
    GameManager& gm = GameManager::m_Get();
    return gm.m_hubSceneIndex;
}

Scene *GameManager::GetActiveScene() {
    GameManager& gm = GameManager::m_Get();
    return gm.m_activeScene;
}

DataLoader &GameManager::GetGameData() {
    GameManager& gm = GameManager::m_Get();
    return *(gm.m_gameData);
}

WINDOW *GameManager::GetTextWindow() {
    GameManager& gm = GameManager::m_Get();
    return gm.m_textWindow;
}

WINDOW *GameManager::GetGameWindow() {
    GameManager& gm = GameManager::m_Get();
    return gm.m_gameWindow;
}

bool GameManager::LoadScene(int sceneIndex) {
    GameManager& gm = GameManager::m_Get();

    // Check if index valid
    if(sceneIndex > (int)gm.m_gameData->ConfigSceneCount()-1){
        ShowError(" Trying to load scene beyond max config defined scene\n");
        return false;
    }

    // Try load & replace scene
    Scene * oldScene = gm.m_activeScene;
    int oldSceneIndex = gm.m_activeSceneIndex;
    try {
        // Try to create new scene with provided index
        gm.m_activeScene = new Scene(sceneIndex);
        gm.m_activeSceneIndex = sceneIndex;

        // Scene successfully loaded - try call Start on objects
        for (auto obj : gm.m_activeScene->sceneObjects)
            obj->Start();
    }
    catch (exception& e){
        ShowError(" Loading scene " + to_string(sceneIndex) + " failed due to:\n" + string(e.what()) + "\n");
        gm.m_activeScene = oldScene;
        gm.m_activeSceneIndex = oldSceneIndex;
        return false;
    }
    delete oldScene;
    return true;
}

void GameManager::ShowError(const std::string &message) {
    GameManager& gm = GameManager::m_Get();

    // Clear window & show error message
    wclear(gm.m_gameWindow);
    mvwprintw(gm.m_gameWindow, 1, 0, " Runtime error:\n%s\n Press any key to continue...", message.c_str());
    RefreshWindows();

    // Enable blocking input & wait for any keypress
    nodelay(gm.m_gameWindow, false);
    wgetch(gm.m_gameWindow);
    nodelay(gm.m_gameWindow, true);

    // Refresh back to game mode
    RefreshWindows();
}

void GameManager::ExitGame() {
    GameManager& gm = GameManager::m_Get();
    gm.m_gameState = EXIT;
}

void GameManager::RefreshWindows() {
    GameManager& gm = GameManager::m_Get();
    box(gm.m_gameWindow, 0, 0);
    box(gm.m_textWindow, 0, 0);
    wrefresh(gm.m_gameWindow);
    wrefresh(gm.m_textWindow);
}

void GameManager::m_InitGameWindows(){
    int termSizeY = 0;
    int termSizeX = 0;
    getmaxyx(stdscr,termSizeY,termSizeX); // Retrieve size of terminal window

    // Calc y and x starting coordinates for game/text windows
    int winStartY = (termSizeY / 2) - ((m_gameWinY + m_textWinY) / 2);
    int winStartX = (termSizeX / 2) - (m_gameWinX / 2);
    // Create game/text windows
    m_gameWindow = newwin(m_gameWinY, m_gameWinX, winStartY, winStartX);
    m_textWindow = newwin(m_textWinY, m_gameWinX, winStartY + m_gameWinY, winStartX);

    // Enable non-blocking input mode on all windows
    nodelay(stdscr, true);
    nodelay(m_textWindow, true);
    nodelay(m_gameWindow, true);

    // Enable terminal color mode & set color pairs
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
}


bool GameManager::m_CheckTerminal() const{
    ostringstream errorMsg;

    int y,x;
    getmaxyx(stdscr,y,x); // Gets terminal y,x m_triggerSize
    if(y < m_gameWinY || x < m_gameWinX){
        errorMsg << " Insufficient window m_triggerSize (" << y << ", " << x << ")\n";
        errorMsg << " Required minimum is (" << m_gameWinY << ", " << m_gameWinX << ")\n";
    }

    if(!has_colors())
        errorMsg << " Terminal does not support colors\n";

    if(!errorMsg.str().empty()){
        ShowError(errorMsg.str());
        return false;
    }

    return true;
}

bool GameManager::m_Initialize(char * gameConfigPath) {
    // Allocate new gameData instance
    m_gameData = new DataLoader();
    if(!m_gameData)
        return false;

    if(!m_gameData->LoadMainConfig(gameConfigPath))
        return false;

    // Try fetch game required variables
    ostringstream missingParams;
    try {
        m_updateRate = m_gameData->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_UPDATE_RATE);
        if(!m_updateRate)
            missingParams << PARAM_UPDATE_RATE << " ";
        m_gameWinY = m_gameData->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_GAME_WIN_Y);
        if(!m_gameWinY)
            missingParams << PARAM_GAME_WIN_Y << " ";
        m_gameWinX = m_gameData->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_GAME_WIN_X);
        if(!m_gameWinX)
            missingParams << PARAM_GAME_WIN_X << " ";
        m_textWinY = m_gameData->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_TEXT_WIN_Y);
        if(!m_textWinY)
            missingParams << PARAM_TEXT_WIN_Y << " ";
        m_menuSceneIndex = m_gameData->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_MENU_SCENE);
        m_hubSceneIndex = m_gameData->ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_HUB_SCENE);
        if(m_menuSceneIndex == m_hubSceneIndex)
            missingParams << PARAM_MENU_SCENE << ", " << PARAM_HUB_SCENE << " not defined or equal";

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

    // Set m_target execution time
    m_targetMs = 1000/m_updateRate;

    // Check for terminal compatibility
    if(!m_CheckTerminal())
        return false;

    // Clear stdscr before creating new windows
    clear();

    // Inits ncurses game&text windows
    m_InitGameWindows();

    // Try load default scene & return result
    return LoadScene(m_menuSceneIndex);
}

void GameManager::m_GameLoop() {
    auto startTime = high_resolution_clock::now();

    m_visualCounter = m_visualCounter < (size_t)m_updateRate ? m_visualCounter+1 : 0;

    // Clear window contents & reset text cursor position
    werase(m_gameWindow);
    werase(m_textWindow);
    wmove(m_textWindow, 1, 0);

    // Print error message if execution time takes longer than m_target
    if(m_waitMs < 0)
        wprintw(m_textWindow, " Cant keep up! Update-rate possibly set too high.\n");
    wprintw(m_textWindow, " Scene: %d | Objects: %03zu | Frame time: %03ld~ms | Debug counter: %03lu\n",
            m_activeSceneIndex, m_activeScene->sceneObjects.size(), m_deltaMs,  m_visualCounter);

    // Update & render all scene objects
    for(auto obj : m_activeScene->sceneObjects){
        if(!obj->active)
            continue;
        if(!obj->Update(max((int)m_deltaMs,1)))
            return;
        obj->Render(m_gameWindow, m_textWindow);
    }

    // Refresh windows for visual changes to take effect
    RefreshWindows();

    auto endTime = high_resolution_clock::now();

    // Get delta based on start - end time & time to wait
    m_deltaMs = duration_cast<milliseconds>(startTime - endTime).count();
    m_deltaMs = m_deltaMs == 0 ? 1 : m_deltaMs;
    m_waitMs = m_targetMs - m_deltaMs;

    // If needed nap so execution matches m_target
    if(m_waitMs > 0)
        napms((int)m_waitMs);
}











