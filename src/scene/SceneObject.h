#pragma once
#include "../utils/Vec2.h"
#include <ncurses.h>
#include <cstdint>
#include <string>

using std::string;

class SceneObject {
public:
    SceneObject() = delete;
    SceneObject(Vec2 pos, bool active, string objectType, string tags);
    SceneObject(const SceneObject& other) = default;
    virtual ~SceneObject() = default;

    virtual void Start();
    virtual bool Update(double updateDelta);
    virtual void Render(WINDOW * gameWin, WINDOW * textWin);

    bool IsType(const string& type);
    bool HasTag(const string& tag);

    Vec2 position;
    bool active;
private:
    string m_objectType;
    string m_tags;
};



