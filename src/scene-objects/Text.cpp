#include "Text.h"

#include <utility>

Text::Text(Vec2 position, bool active, string objectType, string tags, string contents)
        : SceneObject(position, active, std::move(objectType), std::move(tags)),
        m_contents(std::move(contents)), m_startX(0), m_startY(0), m_lines({}){
}

void Text::Start() {
    size_t lastNewline = 0;
    size_t nextNewline = 0;
    string lineString;
    bool hasNewlines = false;
    while ((nextNewline = m_contents.find("!n", lastNewline+2)) != string::npos){
        if(!hasNewlines)
            lineString = m_contents.substr(lastNewline, nextNewline-lastNewline);
        else
            lineString = m_contents.substr(lastNewline+2, nextNewline-lastNewline-2);
        m_lines.push_back(lineString);
        lastNewline = nextNewline;
        m_startY++;
        hasNewlines = true;
    }
    if(hasNewlines)
        m_lines.push_back(m_contents.substr(lastNewline+2));

    if(!hasNewlines)
        m_lines.push_back(m_contents);
}

void Text::Render(WINDOW *gameWin, WINDOW *textWin) {
    int startY = position.y;

    for (auto& line: m_lines) {
        mvwprintw(gameWin, startY, position.x, "%s\n", line.c_str());
        startY++;
    }
}



