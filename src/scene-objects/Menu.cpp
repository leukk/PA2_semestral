#include "Menu.h"

Menu::Menu(const DisplayObject& displayObject) :
        DisplayObject(displayObject),
        choice(0), selectable(true), options({}){
}

void Menu::Start() {
    string optBuffer;
    istringstream optionsStream(m_content);
    while (optionsStream.good()){
        optionsStream >> optBuffer;
        options.push_back(optBuffer);
        optBuffer.clear();
    }
}

bool Menu::Update(int updateDeltaMs) {
    (void) updateDeltaMs;

    if(!selectable || options.empty()){
        choice = 0;
        return true;
    }

    // Change m_choice based on
    if(InputManager::GetKeyUp(KEY_UP))
        choice = choice == 0 ? ((int)options.size() - 1) : choice - 1;
    if(InputManager::GetKeyUp(KEY_DOWN))
        choice = choice == ((int)options.size() - 1) ? 0 : choice + 1;

    return true;
}

void Menu::Render(WINDOW *gameWin, WINDOW *textWin) {
    int winY, winX;
    getmaxyx(gameWin, winY, winX);
    int optionIndex = 0;
    int startY = position == Vec2::Zero() ? (winY/2) : position.y;

    wattron(gameWin, COLOR_PAIR(m_color));
    for(auto& option : options){
        // Highlight render string if selected
        bool selectOpt = choice == optionIndex && selectable;
        string renderString = selectOpt ? "> " + option + " <" : option;

        // Calculate print position & print
        int startX = position == Vec2::Zero() ? (winX/2) - ((int)renderString.size()/2) : position.x - ((int)renderString.size()/2);

        if(selectOpt)
            wattron(gameWin, A_BOLD);
        mvwprintw(gameWin, startY, startX, "%s", renderString.c_str());
        if(selectOpt)
            wattroff(gameWin, A_BOLD);

        startY++;
        optionIndex++;
    }
    wattroff(gameWin, COLOR_PAIR(m_color));

    wprintw(textWin, " Menu selected option: %d\n", choice);
}
