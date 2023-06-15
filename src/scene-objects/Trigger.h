#pragma once
#include "../singleton-managers/GameManager.h"
#include "../scene-base/SceneObject.h"
#include "../structs/Vec2.h"
#include <string>

using std::string;
using std::istringstream;

/**
 * Trigger: inherits SceneObject
 *
 * Sets public variable triggered to true when
 * object with target tag within trigger bounds.
 */
class Trigger : public SceneObject{
public:
    Trigger() = delete;
    Trigger(const SceneObject& sceneObject, Vec2 triggerSize, string targetTag);
    Trigger(const Trigger& other) = default;
    ~Trigger() override = default;

    /**
     * Start override
     *
     * Tries fetching object with target tag.
     * Throws if no target object found.
     */
    void Start() override;
    /**
     * Update override
     *
     * Updates triggered state based on target
     * objects position
     * @param updateDeltaMs
     * @return update successful
     */
    bool Update(int updateDeltaMs) override;
    /**
     * Render override
     *
     * Renders trigger borders as + chars
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    bool triggered; /// Triggered state - target object within trigger bounds
protected:
    Vec2 m_triggerSize; /// Trigger bounds size - spans position + triggerSize
    string m_targetTag; /// Target object tag
    SceneObject* m_target; /// Target object dependency pointer
};
