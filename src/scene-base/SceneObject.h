#pragma once
#include "../structs/Vec2.h"
#include <ncurses.h>
#include <string>

using std::string;

class SceneObject {
public:
    SceneObject() = delete;
    SceneObject(Vec2 pos, bool active, string tags);
    SceneObject(const SceneObject& other) = default;
    virtual ~SceneObject() = default;

    virtual void Start();
    virtual bool Update(int updateDeltaMs);
    virtual void Render(WINDOW * gameWin, WINDOW * textWin);

    bool HasTag(const string& tag);
    static bool CheckWindowPosForChar(WINDOW *window, Vec2 pos, const string &charGroup);

public:
    Vec2 position;
    bool active;
protected:
    string m_tags;
};



