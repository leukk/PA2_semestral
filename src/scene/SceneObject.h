#pragma once
#include "../utils/Vec2.h"
#include <ncurses.h>
#include <cstdint>
#include <string>

using std::string;

enum OBJECT_TYPE{
    NONE=0,
    TEXT=1,
    LOGO=2,
    MAIN_MENU=3
};

class SceneObject {
public:
    SceneObject() = delete;
    SceneObject(OBJECT_TYPE objectType, string tags);
    SceneObject(Vec2 pos, Vec2 size, OBJECT_TYPE objectType, string tags);
    SceneObject(const SceneObject& other) = default;
    virtual ~SceneObject() = default;

    virtual void Initialize() = 0;
    virtual void Start() = 0;
    virtual void Update(double updateDelta) = 0;
    virtual void Render(WINDOW * gameWin, WINDOW * textWin) = 0;

    Vec2 position;
    Vec2 size;
private:
    OBJECT_TYPE m_objectType;
    string m_tags;
};



