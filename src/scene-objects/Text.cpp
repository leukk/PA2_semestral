#include "Text.h"

Text::Text(string objectType, string tags, string contents, Vec2 position)
        : SceneObject(position, Vec2::Zero(), std::move(objectType), std::move(tags)),
        m_contents(contents){
}

void Text::Render(WINDOW *gameWin, WINDOW *textWin) {
    int startY = position == Vec2::Zero() ? getmaxy(gameWin) / 2 : position.y;
    int startX = position.x;

    size_t lastNewline = 0;
    size_t nextNewline = 0;
    string renderString;
    bool hasNewlines = false;
    while ((nextNewline = m_contents.find("\\n", lastNewline+2)) != string::npos){
        renderString = m_contents.substr(lastNewline+2, nextNewline-lastNewline-2);
        mvwprintw(gameWin, startY, startX, "%s\n", renderString.c_str());
        lastNewline = nextNewline;
        startY++;
        hasNewlines = true;
    }

    if(!hasNewlines)
        mvwprintw(gameWin, startY, startX, "%s\n", m_contents.c_str());
}

