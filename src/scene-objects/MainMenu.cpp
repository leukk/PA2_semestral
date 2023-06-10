#include "MainMenu.h"

#include <utility>


MainMenu::MainMenu(string objectType, string tags, string name, string description)
    : SceneObject(std::move(objectType), std::move(tags)), m_name(std::move(name)), m_description(std::move(description)),
      m_choice(0), m_options({"New Game", "Load Game", "Info", "Exit"}) {
}

void MainMenu::Update(double updateDelta) {
    (void) updateDelta;
    // Change m_choice based on
    if(InputManager::GetKeyUp(KEY_UP))
        m_choice = m_choice == 0 ? ((int)m_options.size() - 1) : m_choice - 1;
    if(InputManager::GetKeyUp(KEY_DOWN))
        m_choice = m_choice == ((int)m_options.size() - 1) ? 0 : m_choice + 1;
    if(!InputManager::GetKeyUp(KEY_ENTER))
        return;
    switch (m_choice) {
        case 0:
            GameManager::Get().LoadScene(1);
            break;
        case 1:

            break;
    }
}

void MainMenu::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)textWin;

    int winY, winX;
    getmaxyx(gameWin, winY, winX);

    int optionIndex = 0;
    int startY = position == Vec2::Zero() ? (winY/2) : position.y;
    for(auto& option : m_options){
        // Highlight render string if selected
        string renderString = m_choice == optionIndex ? "> " + option + " <" : option;

        // Calculate print position & print
        int startX = position == Vec2::Zero() ? (winX/2) - ((int)renderString.size()/2) : position.x - ((int)renderString.size()/2);
        mvwprintw(gameWin, startY, startX, "%s", renderString.c_str());
        startY++;
        optionIndex++;
    }

    wprintw(textWin, " Menu selected option: %d\n", m_choice);
}

