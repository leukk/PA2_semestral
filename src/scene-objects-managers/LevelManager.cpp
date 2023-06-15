#include "LevelManager.h"

#include <utility>

LevelManager::LevelManager(const SceneObject& sceneObject) :
        SceneObject(sceneObject),
        m_playerInitialPos(Vec2::Zero()), m_playerInitialLives(0),
        m_player(nullptr), m_successTrigger(nullptr), m_abortTrigger(nullptr){
}

void LevelManager::Start() {
    Scene* gameScene = GameManager::GetActiveScene();
    ostringstream missingObjects;

    m_player = dynamic_cast<Player*>(gameScene->GetObjectWithTag(TAG_PLAYER));
    if(!m_player)
        missingObjects << TAG_PLAYER;
    m_abortTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_LEVEL_ABORT_TRIGGER));
    if(!m_abortTrigger)
        missingObjects << TAG_LEVEL_ABORT_TRIGGER;
    m_successTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_LEVEL_SUCCESS_TRIGGER));
    if(!m_successTrigger)
        missingObjects << TAG_LEVEL_SUCCESS_TRIGGER;

    if(!missingObjects.str().empty())
        throw invalid_argument(" Level manager requires objects with following tags:\n" + missingObjects.str());

    // Save players initial position as spawn pos, set lives
    m_playerInitialPos = m_player->position;
    m_playerInitialLives = m_player->remainingLives;
}

bool LevelManager::Update(int updateDeltaMs) {
    (void) updateDeltaMs;
    DataLoader& gameData = GameManager::GetGameData();

    // Player "dead" - respawn
    if(m_player->remainingLives <= 0){
        m_player->position = m_playerInitialPos;
        m_player->remainingLives = m_playerInitialLives;
    }

    // Player in abort trigger - go back to hub
    if(m_abortTrigger->triggered){
        GameManager::LoadScene(GameManager::GetHubSceneIndex());
        return false;
    }

    // Player in success trigger - update player data & go back to hub
    if(m_successTrigger->triggered){
        gameData.playerData.coins += gameData.ConfigLevels()[gameData.playerData.nextLevelIndex].reward;
        gameData.playerData.nextLevelIndex++;
        GameManager::LoadScene(GameManager::GetHubSceneIndex());
        return false;
    }

    return true;
}

void LevelManager::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)gameWin;
    (void)textWin;
}
