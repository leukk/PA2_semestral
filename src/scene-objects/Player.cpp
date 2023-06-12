#include "Player.h"

Player::Player(Vec2 position, bool active, string objectType, string tags)
    : SceneObject(position, active, std::move(objectType), std::move(tags)),
      livesLeft(0), totalSpeed(0), totalRange(0), m_bulletChar("+"), m_playerChar("■"){
}

void Player::Start() {
    DataLoader& gameData = GameManager::GetGameData();
    totalSpeed = gameData.playerData.speed;
    totalRange = gameData.playerData.range;

    for (auto item : gameData.playerData.equippedItems){
        int effect = gameData.ConfigItems()[item].effect;
        int effectChange = gameData.ConfigItems()[item].effectChange;
        switch (effect) {
            case EFFECT_CHANGE_SPEED:
                totalSpeed += effectChange;
                break;
            case EFFECT_CHANGE_RANGE:
                totalRange += effectChange;
                break;
        }
    }

    m_collisionChars = gameData.ConfigGetParam(GameManager::GetActiveSceneIndex(), SHARED_DATA, PARAM_COLLISION);
    m_playerDamageChars = gameData.ConfigGetParam(GameManager::GetActiveSceneIndex(), SHARED_DATA, PARAM_PLAYER_DAMAGE);
}

bool Player::Update(double updateDelta) {
    (void) updateDelta;

    if(InputManager::GetKeyDown(KEY_LEFT)){
        if(m_CheckCollision(position.y, position.x - 1, m_playerDamageChars))
            livesLeft--;
        if(!m_CheckCollision(position.y, position.x - 1, m_collisionChars))
            position.x--;
    }
    if(InputManager::GetKeyDown(KEY_RIGHT)){
        if(m_CheckCollision(position.y, position.x + 1, m_playerDamageChars))
            livesLeft--;
        if(!m_CheckCollision(position.y, position.x + 1, m_collisionChars))
            position.x++;
    }
    if(InputManager::GetKeyDown(KEY_UP)){
        if(m_CheckCollision(position.y - 1, position.x, m_playerDamageChars))
            livesLeft--;
        if(!m_CheckCollision(position.y - 1, position.x, m_collisionChars))
            position.y--;
    }
    if(InputManager::GetKeyDown(KEY_DOWN)){
        if(m_CheckCollision(position.y+1, position.x, m_playerDamageChars))
            livesLeft--;
        if(!m_CheckCollision(position.y+1, position.x, m_collisionChars))
            position.y++;
    }
    return true;
}

void Player::Render(WINDOW *gameWin, WINDOW *textWin) {
    mvwprintw(gameWin, position.y, position.x, "%s", m_playerChar.c_str());
    wprintw(textWin, " Player: lives left: %d", livesLeft);
}

bool Player::m_CheckCollision(int posY, int posX, const string& collisionChars) {
    WINDOW * gameWin = GameManager::GetGameWindow();
    int ch = mvwinch(gameWin, posY, posX);
    for (char m_collisionChar : collisionChars)
        if (ch == (int)m_collisionChar)
            return true;
    return false;
}



