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

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW* gameWindow, WINDOW* textWindow) override;

    void Shoot(Vec2 from, Vec2 dir, int moveDelay, int range);
private:
    string m_collision;
    deque<Bullet> m_bullets;
    WINDOW * m_gameWin;
};
