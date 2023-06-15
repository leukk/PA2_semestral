#include "CharacterObject.h"

CharacterObject::CharacterObject(const DisplayObject &displayObj,
                                 int lives, string collisionChars, string damageChars,
                                 int moveDelayMs, int attackDelayMs, int attackRange, int attackVelocity) :
        DisplayObject(displayObj),
        remainingLives(lives), m_collisionChars(std::move(collisionChars)), m_damageChars(std::move(damageChars)),
        m_moveDelay(moveDelayMs), m_moveTimer(0),
        m_shootDelay(attackDelayMs), m_shootTimer(0), m_shootRange(attackRange), m_shootVelocity(attackVelocity),
        m_dimTimer(0), m_bulletManager(nullptr){
}

bool CharacterObject::Update(int updateDeltaMs) {
    // Update movement & attack & dim timers
    if(m_moveTimer > 0)
        m_moveTimer -= updateDeltaMs;
    if(m_shootTimer > 0)
        m_shootTimer -= updateDeltaMs;
    if(m_dimTimer > 0)
        m_dimTimer -= updateDeltaMs;

    return true;
}

void CharacterObject::Render(WINDOW *gameWin, WINDOW *textWin) {
    if(m_dimTimer > 0)
        wattron(gameWin, A_BOLD);
    DisplayObject::Render(gameWin, textWin);
    if(m_dimTimer > 0)
        wattroff(gameWin, A_BOLD);
}

bool CharacterObject::TryMoveCharacter(Vec2 dir, WINDOW* gameWin) {
    // Move character if delay is over
    if(m_moveTimer > 0)
        return false;

    // Check if destination damaging, if so subtract lives
    if(CheckWindowPosForChar(gameWin, position + dir, m_damageChars)){
        remainingLives--;
        m_dimTimer = HIT_DIM_MS;
        return false;
    }

    // Check if destination collider
    if(CheckWindowPosForChar(gameWin, position + dir, m_collisionChars))
        return false;

    // Reset movement delay timer & move
    m_moveTimer = m_moveDelay;
    position += dir;
    return true;
}




