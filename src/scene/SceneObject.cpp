#include "SceneObject.h"

#include <utility>

SceneObject::SceneObject(string objectType, string tags) :
    position(Vec2::Zero()), size(Vec2::Zero()), m_objectType(std::move(objectType)), m_tags(std::move(tags)) {
}

SceneObject::SceneObject(Vec2 pos, Vec2 size, string objectType, string tags) :
    position(pos), size(size), m_objectType(std::move(objectType)), m_tags(std::move(tags)){
}

void SceneObject::Initialize() {

}

void SceneObject::Start() {

}

void SceneObject::Update(double updateDelta) {
    (void)updateDelta;
}

void SceneObject::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)gameWin;
    (void)textWin;
}




