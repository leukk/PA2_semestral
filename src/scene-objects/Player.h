#pragma once
#include "../singleton-managers/GameManager.h"
#include "../singleton-managers/InputManager.h"
#include "../scene-base/CharacterObject.h"
#include "../structs/Vec2.h"

/**
 * Player: inherits CharacterObject
 *
 * Users playable object.
 */
class Player : public CharacterObject {
public:
    Player() = delete;
    Player(const Player& other) = default;
    explicit Player(const CharacterObject& characterObject);
    ~Player() override = default;

    /**
     * Start override
     *
     * Applies bonus stats & fetches
     * bulletManager pointer
     */
    void Start() override;
    /**
     * Update override
     *
     * Moves / shoots based on user input.
     * @param updateDeltaMs
     * @return
     */
    bool Update(int updateDeltaMs) override;
    /**
     * Render override
     *
     * Renders character using base DisplayObject.
     * Renders additional player info to text window.
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    /**
     * Applies bonus effects (from creation/items)
     * on top of base config stats
     */
    void AddBonusEffects();
private:
    Vec2 m_lastMoveDir; /// Last movement direction vector - used for shooting
    int m_roleActionDelay; /// Role action delay
    int m_roleActionTimer; /// Role action timer
};
