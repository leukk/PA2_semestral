#include "Trigger.h"

Trigger::Trigger(Vec2 position, bool active, string objectType, string tags, string targetTag, Vec2 size) :
        SceneObject(position, active, objectType, tags),
        triggered(false), triggerSize(size), m_targetTag(targetTag), m_target(nullptr){
}

void Trigger::Start() {
    m_target = GameManager::GetActiveScene()->GetObjectWithTag(m_targetTag);
    if(!m_target)
        throw invalid_argument("Trigger couldn't find target object, target object tag: " + m_targetTag);
}

bool Trigger::Update(double deltaS) {
    (void)deltaS;
    triggered = (m_target->position.x >= position.x && m_target->position.x <= position.x + triggerSize.x
            && m_target->position.y >= position.y && m_target->position.y <= position.y + triggerSize.y);
    return true;
}

void Trigger::Render(WINDOW *gameWin, WINDOW *textWin) {
    mvwprintw(gameWin, position.y, position.x, "+");
    mvwprintw(gameWin, position.y+triggerSize.y, position.x+triggerSize.x, "+");
}
