#include "Enemy.h"

Enemy::Enemy(Vec2 position, bool active, string objectType, string tags, Vec2 moveDir, int moveSpeed) :
        SceneObject(position, active, objectType, tags), m_collision({}), m_enemyChar({}), m_bulletChar({}),
        m_moveSpeed(moveSpeed), m_moveDir(moveDir) {
}

void Enemy::Start() {
}

bool Enemy::Update(double updateDelta) {
    return true;
}

void Enemy::Render(WINDOW *gameWin, WINDOW *textWin) {
    SceneObject::Render(gameWin, textWin);
}

bool Enemy::m_CheckCollision(int posY, int posX, const string& collisionChars) {
    WINDOW * gameWin = GameManager::GetGameWindow();
    int ch = mvwinch(gameWin, posY, posX);
    for (char m_collisionChar : collisionChars)
        if (ch == (int)m_collisionChar)
            return true;
    return false;
}
