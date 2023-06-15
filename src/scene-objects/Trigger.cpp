#include "Trigger.h"

#include <utility>

Trigger::Trigger(const SceneObject& sceneObject, Vec2 triggerSize, string targetTag) :
        SceneObject(sceneObject),
        triggered(false), m_triggerSize(triggerSize), m_targetTag(std::move(targetTag)), m_target(nullptr){
}

void Trigger::Start() {
    m_target = GameManager::GetActiveScene()->GetObjectWithTag(m_targetTag);
    if(!m_target)
        throw invalid_argument(" Trigger couldn't find target object, target object tag: " + m_targetTag);
}

bool Trigger::Update(int updateDeltaMs) {
    (void)updateDeltaMs;
    // Target object within trigger bounds
    triggered = (m_target->position.x >= position.x && m_target->position.x <= position.x + m_triggerSize.x
            && m_target->position.y >= position.y && m_target->position.y <= position.y + m_triggerSize.y);
    return true;
}

void Trigger::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)textWin;
    // Print + on edges of trigger bounds
    mvwprintw(gameWin, position.y, position.x, "+");
    mvwprintw(gameWin, position.y + m_triggerSize.y, position.x + m_triggerSize.x, "+");
    mvwprintw(gameWin, position.y + m_triggerSize.y, position.x, "+");
    mvwprintw(gameWin, position.y, position.x + m_triggerSize.x, "+");
}
