#include "Menu.h"

Menu::Menu(Vec2 position, bool active, string objectType, string tags, string optString) :
        SceneObject(position, active, objectType, tags){
    string optBuffer;
    istringstream optionsStream(optString);
    while (optionsStream.good()){
        optionsStream >> optBuffer;
        options.push_back(optBuffer);
        optBuffer.clear();
    }
}

void Menu::Start() {
    SceneObject::Start();
}

bool Menu::Update(double updateDelta) {
    (void) updateDelta;

    if(!selectable)
        return true;

    // Change m_choice based on
    if(InputManager::GetKeyUp(KEY_UP))
        choice = choice == 0 ? ((int)options.size() - 1) : choice - 1;
    if(InputManager::GetKeyUp(KEY_DOWN))
        choice = choice == ((int)options.size() - 1) ? 0 : choice + 1;

    return true;
}

void Menu::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)textWin;

    int winY, winX;
    getmaxyx(gameWin, winY, winX);
    int optionIndex = 0;
    int startY = position == Vec2::Zero() ? (winY/2) : position.y;

    for(auto& option : options){
        // Highlight render string if selected
        string renderString = choice == optionIndex && selectable ? "> " + option + " <" : option;

        // Calculate print position & print
        int startX = position == Vec2::Zero() ? (winX/2) - ((int)renderString.size()/2) : position.x - ((int)renderString.size()/2);
        mvwprintw(gameWin, startY, startX, "%s", renderString.c_str());
        startY++;
        optionIndex++;
    }

    wprintw(textWin, " Menu selected option: %d\n", choice);
}
