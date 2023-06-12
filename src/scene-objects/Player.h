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

private:
    static bool m_CheckCollision(int y, int x, const string& collisionChars);

public:
    int livesLeft;
    int totalSpeed;
    int totalRange;

private:
    string m_collisionChars;
    string m_playerDamageChars;
    string m_bulletChar;
    string m_playerChar;
};
