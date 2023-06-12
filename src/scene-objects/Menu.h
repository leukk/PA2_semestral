#pragma once
#include "../scene/SceneObject.h"
#include "../managers/GameManager.h"
#include <vector>
#include <sstream>

using std::istringstream;
using std::vector;

class Menu : public SceneObject{
public:
    Menu() = delete;
    Menu(Vec2 position, bool active, string objectType, string tags, string optString);
    Menu(const Menu& other) = default;
    ~Menu() override = default;

    void Start() override;
    bool Update(double deltaS) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    int choice = 0;
    bool selectable = true;
    vector<string> options{};
};

