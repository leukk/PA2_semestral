#pragma once
#include "../utils/Vec2.h"
#include "../managers/InputManager.h"
#include "../scene/SceneObject.h"
#include <ncurses.h>

class Enemy : public SceneObject {
public:
    Enemy() = delete;
    Enemy(const Enemy& other) = default;
    Enemy(Vec2 position, bool active, string objectType, string tags,
          Vec2 moveDir, int moveSpeed);
    ~Enemy() override = default;

    void Start() override;
    bool Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    bool m_CheckCollision(int posY, int posX, const string& collisionChars);

private:
    string m_collision{};
    string m_enemyChar{};
    string m_bulletChar{};

    int m_moveSpeed;
    Vec2 m_moveDir;
};