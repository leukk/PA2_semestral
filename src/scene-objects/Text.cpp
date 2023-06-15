#include "Text.h"

Text::Text(const DisplayObject& displayObject) :
    DisplayObject(displayObject),
    m_wcontent({}){
}

void Text::SetContents(const string &contents) {
    m_content = contents;
}

void Text::Start() {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    m_wcontent = converter.from_bytes(m_content);
}

bool Text::Update(int updateDeltaMs) {
    (void)updateDeltaMs;
    return true;
}

void Text::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)textWin;
    int printY = position.y;
    int printX = position.x;

    wattron(gameWin, COLOR_PAIR(m_color));
    for (auto ch : m_wcontent) {
        if (!iswspace(ch) && ch != L'!')
            mvwaddnwstr(gameWin, printY, printX, &ch, 1);
        printX++;
        if (ch == L'!') {
            printY++;
            printX = position.x;
        }
    }
    wattroff(gameWin, COLOR_PAIR(m_color));
}




