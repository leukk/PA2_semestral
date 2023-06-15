#pragma once
#include "../scene-objects-managers/BulletManager.h"
#include "../utils/GameConstants.h"
#include "DisplayObject.h"
#include <string>

using std::string;

/**
 * DisplayObject derived base class.
 *
 * Adds common character variables and provides state Update & Rendering implementation
 * @note Standalone serves little to no purpose.
 */
class CharacterObject : public DisplayObject{
public:
    CharacterObject() = delete;
    explicit CharacterObject(const DisplayObject& displayObj,
                             int lives, string collisionChars, string damageChars,
                             int moveDelayMs, int attackDelayMs, int attackRange, int attackVelocity);
    CharacterObject(const CharacterObject& other) = default;
    ~CharacterObject() override = default;


    /**
     * Update override
     *
     * Updates characters timers
     * @param updateDeltaMs
     * @return update successful
     */
    bool Update(int updateDeltaMs) override;
    /**
     * Render override
     *
     * Renders m_content to game window using
     * DisplayObjects base implementation
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    /**
     * Tries to move character in direction in given window.
     *
     * Tries to move, first checks for collision, then for damaging
     * chars & moves / subtracts lives accordingly.
     * @param dir direction to move in
     * @param gameWin game window
     * @return moving successful
     */
    bool TryMoveCharacter(Vec2 dir, WINDOW* gameWin);

    int remainingLives; /// Remaining lives of character
protected:
    string m_collisionChars; /// Chars which character cant go over
    string m_damageChars; /// Chars which damage character - subtract lives
    int m_moveDelay; /// Movement step delay
    int m_moveTimer; /// Movement delay timer
    int m_shootDelay; /// In between shots delay
    int m_shootTimer; /// Shoot delay timer
    int m_shootRange; /// Range which characters bullets travel
    int m_shootVelocity; /// Speed at which characters bullets travel
    int m_dimTimer; /// Dim effect on hit timer

    BulletManager * m_bulletManager; /// Bullet manager pointer - shooting disabled if null
};

