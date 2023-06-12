#pragma once
#include "../scene/SceneObject.h"
#include "../managers/GameManager.h"
#include <vector>
#include <sstream>

using std::istringstream;
using std::vector;

class Trigger : public SceneObject{
public:
    Trigger() = delete;
    Trigger(Vec2 position, bool active, string objectType, string tags, string targetTag, Vec2 size);
    Trigger(const Trigger& other) = default;
    ~Trigger() override = default;

    void Start() override;
    bool Update(double deltaS) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    bool triggered;
    Vec2 triggerSize;
private:
    string m_targetTag;
    SceneObject* m_target;
};
