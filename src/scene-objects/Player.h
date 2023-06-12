#pragma once
#include "../managers/InputManager.h"
#include "../scene/SceneObject.h"
#include <ncurses.h>

class Player : public SceneObject {
public:
    Player() = delete;
    Player(const Player& other) = default;
    Player(Vec2 position, bool active, string objectType, string tags);
    ~Player() override = default;

    void Start() override;
    bool Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    int m_speed;
    int m_range;
private:
    string m_playerChar;
};
