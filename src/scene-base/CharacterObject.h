#pragma once
#include "../scene-objects-managers/BulletManager.h"
#include "../utils/GameConstants.h"
#include "DisplayObject.h"
#include <string>

using std::string;

class CharacterObject : public DisplayObject{
public:
    CharacterObject() = delete;
    explicit CharacterObject(const DisplayObject& displayObj,
                             int lives, string collisionChars, string damageChars,
                             int moveDelayMs, int attackDelayMs, int attackRange, int attackVelocity);
    CharacterObject(const CharacterObject& other) = default;
    ~CharacterObject() override = default;

    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    bool TryMoveCharacter(Vec2 dir, WINDOW* gameWin);

    int remainingLives;
protected:
    string m_collisionChars;
    string m_damageChars;
    int m_moveDelay;
    int m_moveTimer;
    int m_shootDelay;
    int m_shootTimer;
    int m_shootRange;
    int m_shootVelocity;
    int m_dimTimer;

    BulletManager * m_bulletManager;
};

