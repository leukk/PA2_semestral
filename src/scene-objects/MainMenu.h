#pragma once
#include "../singletons/InputManager.h"
#include "../singletons/GameManager.h"
#include "../scene/SceneObject.h"
#include <array>
#include <ncurses.h>

using std::array;

class MainMenu : public SceneObject{
public:
    MainMenu() = delete;
    MainMenu(OBJECT_TYPE objectType, string tags, string name, string description);
    MainMenu(const MainMenu& other) = default;
    ~MainMenu() override = default;

    void Initialize() override;
    void Start() override;
    void Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    string m_name;
    string m_description;

    int m_choice;
    array<string, 4> m_options;
};


