#include "GameConstants.h"
#include "singletons/GameManager.h"
#include <chrono>
#include <ncurses.h>
#include <cmath>
#include <fstream>
#include <string>

using std::min;
using std::chrono::high_resolution_clock, std::chrono::milliseconds, std::chrono::duration_cast;

string GetMainConfigPath(char * argConfig){
    string configPath;
    if(!argConfig)
        printw("No config passed as argument.\n");
    else
        configPath = argConfig;

    // Try open ifstream of main config file
    ifstream configStream(configPath);
    while(!configStream.is_open()){
        char inputPath[200];

        printw("Could not open config file, try entering path again:\n");
        echo();
        getnstr(inputPath, 199);
        noecho();

        configPath = inputPath;
        configStream.open(configPath);
    }

    // Found file which can be read
    configStream.close();
    return configPath;
}

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

    string gameConfigPath = GetMainConfigPath(argc[1]);

    // Get reference to GameManager singleton
    GameManager& gameManager = GameManager::Get();
    gameManager.Initialize(gameConfigPath);

    // Enable non-blocking input mode after configuration is done
    nodelay(stdscr, true);

    int64_t targetMs = 1000 / GAME_UPDATE_RATE; // Target execution time in ms
    int64_t deltaMs = targetMs; // Measured execution time in ms
    int64_t waitMs; // How long to wait in case execution is faster than target

    // Timed while loop with execution delta
    while(true){
        auto startTime = high_resolution_clock::now();

        // Execute game update
        // if(!gameSceneManager.gameLoop(deltaMs))
        //      break;

        auto endTime = high_resolution_clock::now();

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

        printw("Update\n");

        refresh();
    }

    SafeExit(EXIT_SUCCESS);
}


