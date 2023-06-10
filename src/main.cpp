#include "utils/DataLoader.h"
#include "managers/GameManager.h"
#include "managers/InputManager.h"
#include <ncurses.h>
#include <cmath>
#include <locale>

/**
 * NCurses initialization function.\n
 * Calls all relevant ncurses functions to init terminal/screen.
 */
void InitializeNCurses(){
    setlocale(LC_ALL, ""); // Set locale to work
    initscr(); // Init ncurses
    start_color(); // Enable color mode
    noecho(); // Turn off terminal echoing
    cbreak(); // Turn off character buffering (except terminal control characters such as CTRL-C,Z,V...)
    keypad(stdscr, true); // Enables reading of keypad/F-Number keys in an interactive manner
}

void SafeExit(int status){
    // End ncurses mode & exit program
    endwin();
    exit(status);
}

int main([[maybe_unused]] int argv, char * argc[]){
    InitializeNCurses();

    // Load config from filepath provided in argc or by user
    DataLoader dataLoader;
    if(!dataLoader.LoadMainConfig(argc[1]))
        SafeExit(EXIT_FAILURE);

    clear();

    // Get reference to GameManager singleton & initialize it
    GameManager& gameManager = GameManager::Get();
    if(!gameManager.Initialize(&dataLoader))
        SafeExit(EXIT_FAILURE);

    wclear(gameManager.textWindow);
    wclear(gameManager.gameWindow);

    // Get reference to InputManager singleton
    InputManager& inputManager = InputManager::m_Get();

    // Enable non-blocking input mode & clear stdscr after configuration is done
    nodelay(stdscr, true);


    while(true){
        // Fetch input & update game afterward
        inputManager.m_PollInput();
        gameManager.m_GameLoop();

        if(gameManager.GetGameState() == EXIT)
            break;
    }

    SafeExit(EXIT_SUCCESS);
}


