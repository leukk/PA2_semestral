#pragma once
#include "../utils/GameConstants.h"
#include "../scene-base/DisplayObject.h"
#include "../structs/Bullet.h"
#include <ncurses.h>
#include <deque>

using std::deque;

class BulletManager : public DisplayObject{
public:
    BulletManager() = delete;
    explicit BulletManager(const DisplayObject& sceneObject, string collision);
    BulletManager(const BulletManager& other) = default;
    ~BulletManager() override = default;

    /**
     * On scene start override
     *
     * Sets up bullet pool
     */
    void Start() override;
    /**
     * On scene update override
     *
     * Updates state of bullet pool
     * @param updateDeltaMs
     * @return update successful
     */
    bool Update(int updateDeltaMs) override;
    /**
     * On render override
     *
     * Renders bullets to game window using contents string
     * and color
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW* gameWindow, WINDOW* textWindow) override;

    /**
     * Shoots bullet & takes care of its lifetime
     *
     * Shoots bullet from position adding dir every moveDelay
     * reset until bullet collides with one of m_collision chars
     * or runs out of range
     * @param from position from which bullet originates
     * @param dir bullet travel direction
     * @param moveDelay bullet moveDelay
     * @param range bullet range
     */
    void Shoot(Vec2 from, Vec2 dir, int moveDelay, int range);
private:
    string m_collision; /// Bullet collision characters
    deque<Bullet> m_bullets; /// Bullet pool
    WINDOW * m_gameWin; /// Game window pointer
};
