#pragma once
#include "../scene/SceneObject.h"
#include "Player.h"

class Player;
class Trigger;

class LevelManager : public SceneObject {
public:
    LevelManager() = delete;
    LevelManager(const LevelManager& other) = default;
    LevelManager(Vec2 position, bool active, string objectType, string tags, Vec2 playerSpawnPos);
    ~LevelManager() override = default;

    void Start() override;
    bool Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    Vec2 m_playerSpawnPos;
    int m_playerTotalLives;

    Player * m_player;
    Trigger * m_successTrigger;
    Trigger * m_abortTrigger;
    vector<SceneObject*> m_collectibles;
};
