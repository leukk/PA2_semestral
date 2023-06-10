#pragma once
#include "../scene/SceneObject.h"

class Text : public SceneObject{
public:
    Text() = delete;
    Text(string objectType, string tags, string contents, Vec2 position);
    Text(const Text& other) = default;
    ~Text() override = default;

    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    string m_contents;
};

