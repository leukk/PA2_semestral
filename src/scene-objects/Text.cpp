#include "Text.h"

Text::Text(Vec2 position, bool active, string objectType, string tags, string contents)
        : SceneObject(position, active, std::move(objectType), std::move(tags)),
        m_contents(std::move(contents)), m_startX(0), m_startY(0), m_lines({}){
}

void Text::SetContents(const string &contents) {
    m_lines.clear();
    size_t lastNewline = 0;
    size_t nextNewline = 0;
    string lineString;
    bool hasNewlines = false;
    while ((nextNewline = contents.find("!n", lastNewline+2)) != string::npos){
        if(!hasNewlines)
            lineString = contents.substr(lastNewline, nextNewline-lastNewline);
        else
            lineString = contents.substr(lastNewline+2, nextNewline-lastNewline-2);
        m_lines.push_back(lineString);
        lastNewline = nextNewline;
        m_startY++;
        hasNewlines = true;
    }
    if(hasNewlines)
        m_lines.push_back(contents.substr(lastNewline+2));

    if(!hasNewlines)
        m_lines.push_back(contents);
}

void Text::Start() {
    SetContents(m_contents);
}

void Text::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)textWin;
    int startY = position.y;

    for (auto& line: m_lines) {
        mvwprintw(gameWin, startY, position.x, "%s\n", line.c_str());
        startY++;
    }
}



