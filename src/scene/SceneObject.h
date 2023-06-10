#pragma once
#include "../utils/Vec2.h"
#include <ncurses.h>
#include <cstdint>
#include <string>

using std::string;

class SceneObject {
public:
    SceneObject() = delete;
    SceneObject(string objectType, string tags);
    SceneObject(Vec2 pos, Vec2 size, string objectType, string tags);
    SceneObject(const SceneObject& other) = default;
    virtual ~SceneObject() = default;

    virtual void Initialize();
    virtual void Start();
    virtual void Update(double updateDelta);
    virtual void Render(WINDOW * gameWin, WINDOW * textWin);

    Vec2 position;
    Vec2 size;
private:
    string m_objectType;
    string m_tags;
};



