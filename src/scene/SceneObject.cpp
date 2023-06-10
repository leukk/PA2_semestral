#include "SceneObject.h"

#include <utility>

SceneObject::SceneObject(Vec2 pos, bool active, string objectType, string tags) :
    position(pos), active(active), m_objectType(std::move(objectType)), m_tags(std::move(tags)){
}

void SceneObject::Initialize() {
}

void SceneObject::Start() {
}

bool SceneObject::Update(double updateDelta) {
    (void)updateDelta;
    return true;
}

void SceneObject::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)gameWin;
    (void)textWin;
}

bool SceneObject::HasTag(const string& tag) {
    return m_tags.find(tag) != string::npos;
}

bool SceneObject::IsType(const string &type) {
    return m_objectType == type;
}




