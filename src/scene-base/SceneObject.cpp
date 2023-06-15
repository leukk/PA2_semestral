#include "SceneObject.h"

SceneObject::SceneObject(Vec2 pos, bool active, string tags) :
    position(pos), active(active), m_tags(std::move(tags)){
}

bool SceneObject::HasTag(const string& tag) {
    return m_tags.find(tag) != string::npos;
}

bool SceneObject::CheckWindowPosForChar(WINDOW *window, Vec2 pos, const string &charGroup) {
    // Check if char at screenPos in charGroup
    int screenCh = mvwinch(window, pos.y, pos.x);
    screenCh &= A_CHARTEXT;
    for (char ch : charGroup)
        if (screenCh == (int)ch)
            return true;
    return false;
}

void SceneObject::Start() {
    (void) position;
}

bool SceneObject::Update(int updateDeltaMs) {
    (void) updateDeltaMs;
    return true;
}

void SceneObject::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void) gameWin;
    (void) textWin;
}





