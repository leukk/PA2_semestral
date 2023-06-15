#include "singleton-managers/GameManager.h"
#include "singleton-managers/InputManager.h"
#include <ncurses.h>
#include <cmath>
#include <locale>


/**
 * NCurses initialization function
 * Calls all relevant ncurses functions to init terminal/screen.
 */
void InitializeNCurses(){
    setlocale(LC_ALL, ""); // Set locale
    initscr(); // Init ncurses
    noecho(); // Turn off terminal echoing
    cbreak(); // Turn off character buffering (except terminal control characters such as CTRL-C,Z,V...)
    keypad(stdscr, true); // Enables reading of keypad/F-Number keys in an interactive manner
    curs_set(0); // Sets cursor as invisible
}

/**
 * Exits program and turns off curses mode
 * @param status in - program exit status
 */
void SafeExit(int status){
    delwin(GameManager::GetGameWindow());
    delwin(GameManager::GetTextWindow());
    endwin();
    exit_curses(status);
}

int main([[maybe_unused]] int argv, char * argc[]){
    InitializeNCurses();

    init_pair(0, COLOR_BLUE, COLOR_BLACK);

    // Get reference to GameManager singleton & initialize it
    GameManager& gameManager = GameManager::m_Get();
    if(!gameManager.m_Initialize(argc[1]))
        SafeExit(EXIT_FAILURE);

    // Get reference to InputManager singleton
    InputManager& inputManager = InputManager::m_Get();

    while(true){
        // Fetch player input
        inputManager.m_PollInput();
        // Update game
        gameManager.m_GameLoop();

        if(GameManager::GetGameState() == EXIT)
            break;
    }

    SafeExit(EXIT_SUCCESS);
}