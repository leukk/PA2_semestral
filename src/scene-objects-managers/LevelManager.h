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

    /**
     * On scene start override
     *
     * Fetches all necessary dependencies such as menus, text objects..
     */
    void Start() override;
    /**
     * On scene update override
     *
     * Checks level triggers and finishes/aborts/respawns accordingly
     * @param updateDeltaMs
     * @return update successful
     */
    bool Update(int updateDeltaMs) override;
    /**
     * On render override
     *
     * Has no effect.
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    Vec2 m_playerInitialPos; /// Player spawn position
    int m_playerInitialLives; /// Number of player lives after accounting items

    Player * m_player; /// Player object dependency
    Trigger * m_successTrigger; /// Level finish trigger dependency
    Trigger * m_abortTrigger; /// Level abort trigger dependency
};
