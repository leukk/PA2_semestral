#include "LevelManager.h"

#include <utility>

LevelManager::LevelManager(const SceneObject& sceneObject) :
    SceneObject(sceneObject),
    m_playerSpawnPos(Vec2::Zero()), m_playerTotalLives(0),
    m_player(nullptr), m_successTrigger(nullptr), m_abortTrigger(nullptr),
    m_collectibles({}){
}

void LevelManager::Start() {
    DataLoader& gameData = GameManager::GetGameData();
    Scene* gameScene = GameManager::GetActiveScene();
    ostringstream missingObjects;

    m_player = dynamic_cast<Player*>(gameScene->GetObjectWithTag(PARAM_PLAYER));
    if(!m_player)
        missingObjects << PARAM_PLAYER;
    m_abortTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_LEVEL_ABORT_TRIGGER));
    if(!m_abortTrigger)
        missingObjects << TAG_LEVEL_ABORT_TRIGGER;
    m_successTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_LEVEL_SUCCESS_TRIGGER));
    if(!m_successTrigger)
        missingObjects << TAG_LEVEL_SUCCESS_TRIGGER;
    m_collectibles = gameScene->GetObjectsWithTag(TAG_LEVEL_COLLECT_OBJ);

    if(!missingObjects.str().empty())
        throw invalid_argument(" Level manager requires objects with following tags:\n" + missingObjects.str());

    m_playerSpawnPos = Vec2(gameData.ConfigGetParam(GameManager::GetActiveSceneIndex(), SHARED_DATA, PARAM_PLAYER_SPAWN_POS));

    m_playerTotalLives = gameData.playerData.lives;
    for (auto item : gameData.playerData.equippedItems){
        int effect = gameData.ConfigItems()[item].effect;
        int effectChange = gameData.ConfigItems()[item].effectChange;
        if(effect == EFFECT_CHANGE_LIVES){
            m_playerTotalLives += effectChange;
        }
    }

    m_player->position = m_playerSpawnPos;
    m_player->remainingLives = m_playerTotalLives;
}

bool LevelManager::Update(int updateDeltaMs) {
    (void) updateDeltaMs;
    DataLoader& gameData = GameManager::GetGameData();

    if(m_player->remainingLives <= 0){
        m_player->position = m_playerSpawnPos;
        m_player->remainingLives = m_playerTotalLives;
    }

    if(m_abortTrigger->triggered){
        GameManager::LoadScene(GameManager::GetHubSceneIndex());
        return false;
    }

    if(m_successTrigger->triggered){
        int currentLevelIndex = gameData.playerData.nextLevelIndex;
        gameData.playerData.coins += gameData.ConfigLevels()[currentLevelIndex].reward;
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
