#pragma once
#include "../scene/SceneObject.h"
#include "../managers/GameManager.h"
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
    void SetContents(const string& contents);

private:
    string m_contents;
    int m_startX, m_startY;
    vector<string> m_lines;
};

