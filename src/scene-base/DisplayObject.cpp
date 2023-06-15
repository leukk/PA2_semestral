#include "DisplayObject.h"

#include <utility>

DisplayObject::DisplayObject(const SceneObject& sceneObject, string content, int color) :
        SceneObject(sceneObject),
        m_content(std::move(content)), m_color(color){
}

void DisplayObject::Render(WINDOW *gameWin, WINDOW *textWin) {
    wattron(gameWin, COLOR_PAIR(m_color));
    mvwprintw(gameWin, position.y, position.x, "%s", m_content.c_str());
    wattroff(gameWin, COLOR_PAIR(m_color));
}
