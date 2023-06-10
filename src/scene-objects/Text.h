#pragma once
#include "../managers/GameManager.h"
#include "../scene/SceneObject.h"
#include <vector>

using std::vector;

class Text : public SceneObject{
public:
    Text() = delete;
    Text(Vec2 position, bool active, string objectType, string tags, string contents);
    Text(const Text& other) = default;
    ~Text() override = default;

    void Start() override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    string m_contents;
    int m_startX, m_startY;
    vector<string> m_lines;
};

