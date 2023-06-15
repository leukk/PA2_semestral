#include "BulletManager.h"

#include <utility>

BulletManager::BulletManager(const DisplayObject& sceneObject, string collision) :
        DisplayObject(sceneObject),
        m_collision(std::move(collision)), m_bullets({}), m_gameWin(nullptr){
}

void BulletManager::Start() {
    // Initialize non active bullet pool
    for (int i = 0; i < BULLET_POOL_SIZE; ++i) {
        Bullet bullet;
        m_bullets.push_back(bullet);
    }
}

void BulletManager::Shoot(Vec2 from, Vec2 dir, int moveDelay, int range) {
    Bullet& b = m_bullets.front();
    b.position = from;
    b.direction = dir;
    b.moveDelay = moveDelay;
    b.distanceRemaining = range;
    b.moveTimer = 0;
    b.active = true;
    m_bullets.push_back(b);
}

bool BulletManager::Update(int updateDeltaMs) {
    // Update all bullet positions
    for (auto& b : m_bullets){
        // Check if updating makes sense
        if(!b.active || !m_gameWin)
            continue;
        // Disable if distance ran out
        if(CheckWindowPosForChar(m_gameWin, b.position, m_collision) || b.distanceRemaining <=0){
            b.active = false;
            continue;
        }
        b.moveTimer -= updateDeltaMs;
        if(b.moveTimer <= 0) {
            b.moveTimer = b.moveDelay;
            b.position += b.direction;
            b.distanceRemaining--;
        }
    }
    return true;
}

void BulletManager::Render(WINDOW *gameWindow, WINDOW *textWindow) {
    m_gameWin = gameWindow;
    // Render all bullet to screen
    wattron(gameWindow, COLOR_PAIR(m_color));
    for (auto& b : m_bullets){
        if(!b.active)
            continue;
        mvwprintw(gameWindow, b.position.y, b.position.x, "%s", m_content.c_str());
    }
    wattroff(gameWindow, COLOR_PAIR(m_color));
}
