#pragma once
#include "../managers/InputManager.h"
#include "../managers/GameManager.h"
#include "../scene/SceneObject.h"
#include <array>
#include <ncurses.h>

using std::array;

class MainMenu : public SceneObject{
public:
    MainMenu() = delete;
    MainMenu(Vec2 position, bool active, string objectType, string tags);
    MainMenu(const MainMenu& other) = default;
    ~MainMenu() override = default;

    void Start() override;
    bool Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    int m_choice;
    array<string, 4> m_options;
    bool m_showInfo;
    SceneObject * m_infoTextObject;
};


