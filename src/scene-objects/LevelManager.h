#pragma once
#include "../scene/SceneObject.h"
#include "Player.h"

class Player;

class LevelManager : public SceneObject {
public:
    LevelManager() = delete;
    LevelManager(const LevelManager& other) = default;
    LevelManager(Vec2 position, bool active, string objectType, string tags);
    ~LevelManager() override = default;

    void Start() override;
    bool Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    Player * m_player;
};
