#pragma once
#include "../singleton-managers/GameManager.h"
#include "../singleton-managers/InputManager.h"
#include "../scene-base/CharacterObject.h"
#include "../structs/Vec2.h"
#include <ncurses.h>

class CharacterObject;

/**
 * Enemy: inherits CharacterObject
 *
 * Enemy object - roams back and forth / shoots based on
 * provided move / attack dir.
 */
class Enemy : public CharacterObject {
public:
    Enemy() = delete;
    Enemy(const CharacterObject& other, Vec2 attackDir, Vec2 moveDir);
    Enemy(const Enemy& object) = default;
    ~Enemy() override = default;

    /**
     * Start override
     *
     * Gets bulletManager pointer
     */
    void Start() override;
    /**
     * Update override
     *
     * Updates state, changes position / shoots
     * based on provided parameters.
     * @param updateDeltaMs
     * @return update success
     */
    bool Update(int updateDeltaMs) override;
    /**
     * Render override
     *
     * Renders self using DisplayObject base
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    Vec2 m_attackDir; /// Direction in which enemy attacks
    Vec2 m_moveDir; /// Direction in which enemy roams (reversed on collision)
};