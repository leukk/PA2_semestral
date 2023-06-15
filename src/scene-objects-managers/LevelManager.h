#pragma once
#include "../singleton-managers/GameManager.h"
#include "../scene-base/SceneObject.h"
#include "../scene-objects/Player.h"
#include "../scene-objects/Trigger.h"
#include "../structs/Vec2.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Player;
class Trigger;

class LevelManager : public SceneObject {
public:
    LevelManager() = delete;
    explicit LevelManager(const SceneObject& sceneObject);
    LevelManager(const LevelManager& other) = default;
    ~LevelManager() override = default;

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    Vec2 m_playerSpawnPos;
    int m_playerTotalLives;

    Player * m_player;
    Trigger * m_successTrigger;
    Trigger * m_abortTrigger;
    vector<SceneObject*> m_collectibles;
};
