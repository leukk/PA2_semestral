#include "Player.h"

Player::Player(const CharacterObject& characterObject)
    : CharacterObject(characterObject),
      m_lastMoveDir(Vec2::Zero()),
      m_roleActionDelay(500),
      m_roleActionTimer(0){
}

void Player::Start() {
    // Set player bonus effects
    AddBonusEffects();

    m_bulletManager = dynamic_cast<BulletManager*>(GameManager::GetActiveScene()->GetObjectWithTag(OBJECT_BULLET_MGR));
}

bool Player::Update(int updateDeltaMs) {
    CharacterObject::Update(updateDeltaMs);
    WINDOW * gameWin = GameManager::GetGameWindow();
    DataLoader& gameData = GameManager::GetGameData();

    // Check for damage
    if(CheckWindowPosForChar(gameWin, position, m_damageChars)){
        remainingLives--;
        m_dimTimer = HIT_DIM_MS;
    }

    // Update role action timer
    if(m_roleActionTimer > 0)
        m_roleActionTimer -= updateDeltaMs;

    // Movement / shooting controls
    if(InputManager::GetKeyDown(KEY_LEFT)){
        m_lastMoveDir = Vec2::Left();
        TryMoveCharacter(Vec2::Left(), gameWin);
    }
    if(InputManager::GetKeyDown(KEY_RIGHT)){
        m_lastMoveDir = Vec2::Right();
        TryMoveCharacter(Vec2::Right(), gameWin);
    }
    if(InputManager::GetKeyDown(KEY_UP)){
        m_lastMoveDir = Vec2::Up();
        TryMoveCharacter(Vec2::Up(), gameWin);
    }
    if(InputManager::GetKeyDown(KEY_DOWN)){
        m_lastMoveDir = Vec2::Down();
        TryMoveCharacter(Vec2::Down(), gameWin);
    }
    if(InputManager::GetKeyDown(KEY_SPACE) && m_bulletManager && m_shootTimer <= 0){
        m_bulletManager->Shoot(position, m_lastMoveDir, m_shootVelocity, m_shootRange);
        m_shootTimer = m_shootDelay;
    }

    // Active role abilities
    if(InputManager::GetKeyDown(KEY_ABILITY) && m_bulletManager && m_roleActionTimer <= 0) {
        if (gameData.playerData.role == 0) {
            m_bulletManager->Shoot(position + Vec2::Left(), Vec2::Left(), m_shootVelocity, m_shootRange);
            m_bulletManager->Shoot(position + Vec2::Right(), Vec2::Right(), m_shootVelocity, m_shootRange);
        }
        if (gameData.playerData.role == 1)
            remainingLives++;
        if (gameData.playerData.role == 2) {
            m_bulletManager->Shoot(position + Vec2::Up(), Vec2::Up(), m_shootVelocity, m_shootRange);
            m_bulletManager->Shoot(position + Vec2::Down(), Vec2::Down(), m_shootVelocity, m_shootRange);
            m_bulletManager->Shoot(position + Vec2::Left(), Vec2::Left(), m_shootVelocity, m_shootRange);
            m_bulletManager->Shoot(position + Vec2::Right(), Vec2::Right(), m_shootVelocity, m_shootRange);
        }
        m_roleActionTimer = m_roleActionDelay;
    }

    // Passive role abilities
    if(gameData.playerData.role == 0 && m_shootTimer > 0)
        m_shootTimer -= 4;
    if(gameData.playerData.role == 1 && m_moveTimer > 0)
        m_moveTimer -= 2;

    return true;
}

void Player::Render(WINDOW *gameWin, WINDOW *textWin) {
    CharacterObject::Render(gameWin, textWin);
    wprintw(textWin, " Lives : %d | Range: %d | Attack tmr: %03d | Move tmr: %03d | Role tmr: %03d\n",
            remainingLives, m_shootRange, m_shootTimer, m_moveTimer, m_roleActionTimer);
}

void Player::AddBonusEffects() {
    DataLoader& gameData = GameManager::GetGameData();
    // Add creation bonuses
    remainingLives = gameData.playerData.lives;
    m_moveDelay = gameData.playerData.moveDelay;
    m_shootRange = gameData.playerData.attackRange;

    // Add item bonuses
    for (auto item : gameData.playerData.equippedItems){
        int effect = gameData.ConfigItems()[item].effect;
        int effectChange = gameData.ConfigItems()[item].effectChange;
        if(effect == EFFECT_CHANGE_LIVES){
            remainingLives += effectChange;
        }
        if(effect == EFFECT_CHANGE_RANGE){
            m_shootRange += effectChange;
        }
        if(effect == EFFECT_CHANGE_SPEED){
            m_moveDelay -= effectChange;
        }
    }
}




