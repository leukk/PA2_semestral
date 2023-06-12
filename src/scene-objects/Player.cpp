#include "Player.h"

Player::Player(Vec2 position, bool active, string objectType, string tags)
    : SceneObject(position, active, std::move(objectType), std::move(tags)),
    m_speed(0), m_range(0), m_playerChar("■"){
}

void Player::Start() {
}

bool Player::Update(double updateDelta) {
    (void) updateDelta;

    if(InputManager::GetKeyDown(KEY_LEFT)){
        position.x--;
    }
    if(InputManager::GetKeyDown(KEY_RIGHT)){
        position.x++;
    }
    if(InputManager::GetKeyDown(KEY_UP)){
        position.y--;
    }
    if(InputManager::GetKeyDown(KEY_DOWN)){
        position.y++;
    }
    return true;
}

void Player::Render(WINDOW *gameWin, WINDOW *textWin) {
    mvwprintw(gameWin, position.y, position.x, "%s", m_playerChar.c_str());
}

