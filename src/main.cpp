#include "utils/DataLoader.h"
#include "singletons/GameManager.h"
#include "singletons/InputManager.h"
#include <ncurses.h>
#include <cmath>

/**
 * NCurses initialization function.\n
 * Calls all relevant ncurses functions to init terminal/screen.
 */
void InitializeNCurses(){
    initscr(); // Init ncurses
    start_color(); // Enable color mode
    noecho(); // Turn off terminal echoing
    cbreak(); // Turn off character buffering (except terminal control characters such as CTRL-C,Z,V...)
    keypad(stdscr, true); // Enables reading of keypad/F-Number keys in an interactive manner
}

void SafeExit(int status){
    if(status == EXIT_FAILURE){
        // Disable non-blocking input mode when exiting to show potential exception messages
        nodelay(stdscr, false);

        // Refresh all windows for the last time
        refresh();
        if(GameManager::Get().gameWindow)
            wrefresh(GameManager::Get().gameWindow);
        if(GameManager::Get().textWindow)
            wrefresh(GameManager::Get().textWindow);
        getch();
    }

    // End ncurses mode & exit program
    endwin();
    exit(status);
}

int main([[maybe_unused]] int argv, char * argc[]){
    InitializeNCurses();

    // Load config from filepath provided in argc or by user
    DataLoader dataLoader;
    if(!dataLoader.LoadMainConfig(stdscr, argc[1]))
        SafeExit(EXIT_FAILURE);

    // Get reference to GameManager singleton & initialize it
    GameManager& gameManager = GameManager::Get();
    if(!gameManager.Initialize(dataLoader))
        SafeExit(EXIT_FAILURE);

    // Get reference to InputManager singleton
    InputManager& inputManager = InputManager::m_Get();

    // Enable non-blocking input mode & clear stdscr after configuration is done
    nodelay(stdscr, true);
    clear();

    while(true){
        // Update all managers
        inputManager.m_PollInput();
        gameManager.m_GameLoop();

        if(gameManager.GetGameState() == EXIT)
            break;
    }

    SafeExit(EXIT_SUCCESS);
}


