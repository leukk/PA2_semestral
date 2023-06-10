#include "MainMenu.h"

#include <utility>


MainMenu::MainMenu(Vec2 position, bool active, string objectType, string tags)
    : SceneObject(position, active, std::move(objectType), std::move(tags)),
      m_choice(0), m_options({"New Game", "Load Game", "Info", "Exit"}), m_showInfo(false){
}

void MainMenu::Start() {
    m_infoTextObject = GameManager::Get().activeScene->GetObjectWithTag("info-text");
}


bool MainMenu::Update(double updateDelta) {
    (void) updateDelta;

    // Enable/disable infoObject if found
    if(m_showInfo && InputManager::GetKeyUp(KEY_LEFT)){
        m_showInfo = false;
        if(m_infoTextObject)
            m_infoTextObject->active = false;
    }

    // Change m_choice based on
    if(InputManager::GetKeyUp(KEY_UP))
        m_choice = m_choice == 0 ? ((int)m_options.size() - 1) : m_choice - 1;
    if(InputManager::GetKeyUp(KEY_DOWN))
        m_choice = m_choice == ((int)m_options.size() - 1) ? 0 : m_choice + 1;
    if(InputManager::GetKeyUp(KEY_RIGHT)){
        switch (m_choice) {
            case 0:
                GameManager::Get().LoadScene(1);
                return false;
            case 1:
                GameManager::Get().LoadScene(2);
                return false;
            case 2:
                m_showInfo = true;
                if(m_infoTextObject)
                    m_infoTextObject->active = true;
                return true;
            case 3:
                GameManager::Get().ExitGame();
                return false;
        }
    }
    return true;
}

void MainMenu::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)textWin;

    if(m_showInfo)
        return;

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
