#pragma once
#include "../singleton-managers/GameManager.h"
#include "../singleton-managers/InputManager.h"
#include "../scene-base/CharacterObject.h"
#include "../structs/Vec2.h"

class Player : public CharacterObject {
public:
    Player() = delete;
    Player(const Player& other) = default;
    explicit Player(const CharacterObject& characterObject);
    ~Player() override = default;

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    Vec2 m_lastMoveDir;
    int m_roleActionDelay;
    int m_roleActionTimer;
};
