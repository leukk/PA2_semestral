#pragma once
#include "SceneObject.h"
#include <string>

using std::string;
using std::wstring;

class DisplayObject : public SceneObject {
public:
    DisplayObject() = delete;
    DisplayObject(const SceneObject& sceneObject, string content, int color);
    DisplayObject(const DisplayObject& other) = default;
    ~DisplayObject() override = default;

    void Render(WINDOW * gameWin, WINDOW * textWin) override;

protected:
    string m_content;
    int m_color;
};

