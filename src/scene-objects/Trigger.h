#pragma once
#include "../singleton-managers/GameManager.h"
#include "../scene-base/SceneObject.h"
#include "../structs/Vec2.h"
#include <string>

using std::string;
using std::istringstream;

class Trigger : public SceneObject{
public:
    Trigger() = delete;
    Trigger(const SceneObject& sceneObject, Vec2 triggerSize, string targetTag);
    Trigger(const Trigger& other) = default;
    ~Trigger() override = default;

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    bool triggered;
protected:
    Vec2 m_triggerSize;
    string m_targetTag;
    SceneObject* m_target;
};
