#include "Enemy.h"

Enemy::Enemy(const CharacterObject &object, Vec2 attackDir, Vec2 moveDir) :
        CharacterObject(object),
        m_attackDir(attackDir), m_moveDir(moveDir) {
}

void Enemy::Start() {
    m_bulletManager = dynamic_cast<BulletManager*>(GameManager::GetActiveScene()->GetObjectWithTag(OBJECT_BULLET_MGR));
}

bool Enemy::Update(int updateDeltaMs) {
    // Update base characterObject state
    CharacterObject::Update(updateDeltaMs);

    // Check for damaging characters, if no lives left deactivate
    if(CheckWindowPosForChar(GameManager::GetGameWindow(), position, m_damageChars)){
        remainingLives--;
        m_dimTimer = HIT_DIM_MS;
    }
    if(remainingLives < 1)
        active = false;

    // Try to move in moveDir
    if(!TryMoveCharacter(m_moveDir, GameManager::GetGameWindow()) && m_moveTimer <= 0){
        m_moveDir.x = -m_moveDir.x;
        m_moveDir.y = -m_moveDir.y;
    }

    if(m_bulletManager && m_shootTimer <= 0 && m_shootVelocity && m_shootRange){
        m_bulletManager->Shoot(position, m_attackDir, m_shootVelocity, m_shootRange);
        m_shootTimer = m_shootDelay;
    }

    return true;
}

void Enemy::Render(WINDOW *gameWin, WINDOW *textWin) {
    CharacterObject::Render(gameWin, textWin);
    //wprintw(textWin, " Moving to: %d %d | Delay: %d\n", m_moveDir.x, m_moveDir.y, m_moveTimer);
}




