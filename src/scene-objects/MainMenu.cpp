#include "MainMenu.h"


MainMenu::MainMenu(OBJECT_TYPE objectType, string tags, string name, string description)
    : SceneObject(objectType, std::move(tags)), m_name(std::move(name)), m_description(std::move(description)),
      m_choice(0), m_options({"New Game", "Load Game", "Info", "Exit"}) {
}

void MainMenu::Initialize() { }

void MainMenu::Update(double updateDelta) {
    // Change m_choice based on
    if(InputManager::GetKeyDown(KEY_DOWN))
        m_choice = m_choice == 0 ? m_choice = (int)m_options.size() - 1 : m_choice - 1;
    if(InputManager::GetKeyDown(KEY_UP))
        m_choice = m_choice == (int)m_options.size() - 1 ? 0 : m_choice + 1;
    if(!InputManager::GetKeyDown(KEY_ENTER))
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
    int winY, winX;
    getmaxyx(gameWin, winY, winX);

    int startY = position == Vec2::Zero() ? (winY/2) : position.y;
    for(auto& option : m_options){
        int startX = position == Vec2::Zero() ? (winX/2) - ((int)option.size()/2) : position.x - ((int)option.size()/2);
        mvwprintw(gameWin, startY, startX, "%s", option.c_str());
        startY++;
    }
}

void MainMenu::Start() { }

