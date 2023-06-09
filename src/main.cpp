#include "utils/GameConstants.h"
#include "utils/DataLoader.h"
#include "singletons/GameManager.h"
#include "singletons/InputManager.h"
#include <chrono>
#include <ncurses.h>
#include <cmath>
#include <fstream>
#include <string>

using std::min;
using std::chrono::high_resolution_clock, std::chrono::milliseconds, std::chrono::duration_cast;
using std::ifstream;



/**
 * NCurses initialization function.\n
 * Calls all relevant ncurses functions to init terminal/screen.
 */
void InitializeNCurses(){
    initscr(); // LoadMainConfig screen
    start_color(); // Enable color mode
    noecho(); // Turn off terminal echoing
    cbreak(); // Turn off character buffering (except terminal control characters such as CTRL-C,Z,V...)
    keypad(stdscr, true); // Enables reading of keypad/F-Number keys in an interactive manner
}

/**
 *  Checks if terminal supports all necessary features & is of required size
 *  returns true / false as result
 */
bool CompatibleTerminal(){
    int y,x;
    getmaxyx(stdscr,y,x); // Gets terminal y,x size
    if(y < GAME_WIN_Y || x < GAME_WIN_X){
        printw("Insufficient window size (%d,%d)\n", y, x);
        printw("Required minimum is (%d,%d)\n",GAME_WIN_Y, GAME_WIN_X);
        return false;
    }
    return true;
}

void SafeExit(int status){
    endwin();
    exit(status);
}

int main([[maybe_unused]] int argv, char * argc[]){
    InitializeNCurses();

    // Disable non-blocking input mode during configuration
    nodelay(stdscr, false);

    // Check for terminal compatibility
    if(!CompatibleTerminal())
        SafeExit(EXIT_FAILURE);

    // Load config from filepath provided in argc or by user
    DataLoader dataLoader;
    if(!dataLoader.LoadMainConfig(stdscr, argc[1]))
        SafeExit(EXIT_FAILURE);

    printw("Found %lu scenes\nScene 0 has %lu objects\n"
           "Scene 1 has %lu objects", dataLoader.ConfigSceneCount(), dataLoader.ConfigObjectCount(0), dataLoader.ConfigObjectCount(1));
    refresh();

    // Get reference to GameManager singleton
    GameManager& gameManager = GameManager::Get();
    //gameManager.m_Initialize(dataLoader);

    SafeExit(EXIT_FAILURE);

    // Get reference to InputManager singleton
    InputManager& inputManager = InputManager::m_Get();

    SceneObject* obj = new MainMenu(MAIN_MENU, "main-menu", "Dungeons of Strahov", "some desc");
    obj->Render(gameManager.gameWindow, gameManager.textWindow);
    wrefresh(gameManager.gameWindow);
    getch();

    // Enable non-blocking input mode after configuration is done
    nodelay(stdscr, true);

    int64_t targetMs = 1000 / GAME_UPDATE_RATE; // Target execution time in ms
    int64_t deltaMs = targetMs; // Measured execution time in ms
    int64_t waitMs; // How long to wait in case execution is faster than target

    // Timed while loop with execution delta
    while(true){
        auto startTime = high_resolution_clock::now();

        // Execute game update
        inputManager.m_PollInput();
        gameManager.m_UpdateGame(deltaMs);

        auto endTime = high_resolution_clock::now();

        if(gameManager.GetGameState() == EXIT)
            break;

        // Get delta based on start - end time & time to wait
        deltaMs = duration_cast<milliseconds>(startTime - endTime).count();
        deltaMs = deltaMs == 0 ? 1 : deltaMs;
        waitMs = targetMs - deltaMs;

        // Print error message if execution time takes longer than target
        // Else nap so execution matches target
        if(waitMs < 0)
            wprintw(stdscr, "Cant keep up! Update-rate possibly set too high.\nExecution delta: %ld ms\n", deltaMs);
        else
            napms((int)waitMs);

        refresh();
    }

    SafeExit(EXIT_SUCCESS);
}


