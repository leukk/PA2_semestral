#pragma once
#include "../singleton-managers/GameManager.h"
#include "../singleton-managers/InputManager.h"
#include "../scene-base/CharacterObject.h"
#include "../structs/Vec2.h"
#include <ncurses.h>

class CharacterObject;

class Enemy : public CharacterObject {
public:
    Enemy() = delete;
    Enemy(const CharacterObject& other, Vec2 attackDir, Vec2 moveDir);
    Enemy(const Enemy& object) = default;
    ~Enemy() override = default;

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    Vec2 m_attackDir;
    Vec2 m_moveDir;
};