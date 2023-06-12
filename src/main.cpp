#include "utils/DataLoader.h"
#include "managers/GameManager.h"
#include "managers/InputManager.h"
#include <ncurses.h>
#include <cmath>
#include <locale>

/**
 * NCurses initialization function.
 * Calls all relevant ncurses functions to init terminal/screen.
 */
void InitializeNCurses(){
    setlocale(LC_ALL, ""); // Set locale
    initscr(); // Init ncurses
    start_color(); // Enable color mode
    noecho(); // Turn off terminal echoing
    cbreak(); // Turn off character buffering (except terminal control characters such as CTRL-C,Z,V...)
    keypad(stdscr, true); // Enables reading of keypad/F-Number keys in an interactive manner
}

/**
 * Exits program safely including terminating curses mode.
 * @param status exit program status
 */
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
    GameManager& gameManager = GameManager::m_Get();
    if(!gameManager.m_Initialize(&dataLoader))
        SafeExit(EXIT_FAILURE);


    // Get reference to InputManager singleton
    InputManager& inputManager = InputManager::m_Get();


    while(true){
        // Fetch input & update game afterward
        inputManager.m_PollInput();
        gameManager.m_GameLoop();

        if(GameManager::GetGameState() == EXIT){
            delete gameManager.m_activeScene;
            break;
        }
    }

    SafeExit(EXIT_SUCCESS);
}


