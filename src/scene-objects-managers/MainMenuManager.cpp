#include "MainMenuManager.h"

#include <utility>


MainMenuManager::MainMenuManager(const SceneObject& sceneObject)
    : SceneObject(sceneObject),
      m_state(MAIN_MENU),
      m_upgradeTokens(0), m_usedTokens(0), m_chosenUpgrades({}),
      m_mainMenu(nullptr), m_infoTextObject(nullptr),
      m_buffMenu(nullptr), m_roleMenu(nullptr){
}

void MainMenuManager::Start() {
    Scene* gameScene = GameManager::GetActiveScene();
    ostringstream missingObjects;

    // Get main menu dependencies
    m_mainMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_M_MENU_MENU_OBJ));
    if(!m_mainMenu)
        missingObjects << TAG_M_MENU_MENU_OBJ;
    m_infoTextObject = gameScene->GetObjectWithTag(TAG_M_MENU_INFO_OBJ);
    if(!m_infoTextObject)
        missingObjects << TAG_M_MENU_INFO_OBJ;

    m_buffMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_M_MENU_BUFF_MENU_OBJ));
    if(!m_buffMenu)
        missingObjects << TAG_M_MENU_BUFF_MENU_OBJ;
    m_roleMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_M_MENU_ROLE_MENU_OBJ));
    if(!m_roleMenu)
        missingObjects << TAG_M_MENU_ROLE_MENU_OBJ;

    // Throw if any dependant objects missing
    if(!missingObjects.str().empty())
        throw invalid_argument("Main menu manager required objects with following tags:\n" + missingObjects.str());

    // Throw if invalid buffmenu or rolemenu size
    if(m_buffMenu->options.size() != 3 || m_roleMenu->options.size() != 3)
        throw logic_error("Buff menu / role menu must both have 3 options\n");

    // Get global data
    m_upgradeTokens = GameManager::GetGameData().ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_CREATE_BUFF_TOKENS);
    // Reset chosenUpgrades vector
    m_chosenUpgrades.clear();
    for(size_t i = 0; i < m_buffMenu->options.size(); i++)
        m_chosenUpgrades.push_back(0);
}

bool MainMenuManager::Update(int updateDeltaMs) {
    (void) updateDeltaMs;
    DataLoader& gameData = GameManager::GetGameData();

    // Main menu option selected
    if(m_state == MAIN_MENU && InputManager::GetKeyDown(KEY_RIGHT)){
        switch (m_mainMenu->choice) {
            case 0:
                // Try create new game option:
                try{
                    // set new player data file path
                    gameData.SetPlayerDataFilePath();
                    // set default player stats
                    gameData.SetDefaultPlayerStats();
                    // save player data
                    gameData.SavePlayerData();
                    // continue to buff selection
                    m_state = SELECT_BUFF;
                    m_SetNewGameUi();
                }
                catch (exception& e){
                    GameManager::ShowError(e.what());
                }
                return false;
            case 1:
                // Try load new game option:
                try{
                    // set player data file path
                    gameData.SetPlayerDataFilePath();
                    // try load from path
                    gameData.LoadPlayerData();
                    // if success load hub scene
                    GameManager::LoadScene(GameManager::GetHubSceneIndex());
                }
                catch (exception& e){
                    GameManager::ShowError(e.what());
                }
                return false;
            case 2:
                // Show game info option:
                m_state = INFO;
                m_SetInfoUi();
                return false;
            case 3:
                // Exit game option:
                GameManager::ExitGame();
                return false;
        }
        return true;
    }

    // Go back from info screen on left press
    if(m_state == INFO && InputManager::GetKeyDown(KEY_LEFT)){
        m_state = MAIN_MENU;
        m_SetDefaultMenuUi();
        return false;
    }

    // Buff selection menu
    if(m_state == SELECT_BUFF){
        // Upgrade if tokens remaining
        if(InputManager::GetKeyDown(KEY_RIGHT) && m_usedTokens < m_upgradeTokens){
            m_chosenUpgrades[m_buffMenu->choice] += 1;
            m_usedTokens++;
        }
        // Downgrade & get tokens back if invested in option
        if(InputManager::GetKeyDown(KEY_LEFT) && m_chosenUpgrades[m_buffMenu->choice] > 0){
            m_chosenUpgrades[m_buffMenu->choice] -= 1;
            m_usedTokens--;
        }
        // Enough upgrades selected - move to role selection
        if(m_usedTokens == m_upgradeTokens){
            m_state = SELECT_ROLE;
            m_buffMenu->active = false;
            m_roleMenu->active = true;
            return false;
        }
        return true;
    }

    // Role selection menu
    if(m_state == SELECT_ROLE){
        // Choose role, apply chosen options & proceed to try load hub scene
        if(InputManager::GetKeyDown(KEY_RIGHT)){
            try{
                m_ApplyNewGameOptions();
                gameData.SavePlayerData();
                GameManager::LoadScene(GameManager::GetHubSceneIndex());
            }
            catch (exception& e){
                GameManager::ShowError(e.what());
            }
            return false;
        }
        // Go back to upgrade selection
        if(InputManager::GetKeyDown(KEY_LEFT)){
            m_state = SELECT_BUFF;
            m_SetNewGameUi();
        }
        return true;
    }
    return true;
}

void MainMenuManager::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)gameWin;

    // Render text information based on main menu state
    if(m_state == SELECT_BUFF || m_state == SELECT_ROLE)
        wprintw(textWin, " Creating new game, save file: %s\n", GameManager::GetGameData().PlayerDataPath().c_str());
    if(m_state == SELECT_BUFF){
        wprintw(textWin, " Upgrade your character abilities, %d remaining\n", m_upgradeTokens - m_usedTokens);
        for (size_t i = 0; i < m_buffMenu->options.size(); ++i)
            wprintw(textWin, " %s: %d ", m_buffMenu->options[i].c_str(), m_chosenUpgrades[i]);
    }
    if(m_state == SELECT_ROLE)
        wprintw(textWin, " Select your character role\n");
}

void MainMenuManager::m_SetInfoUi() {
    GameManager::GetActiveScene()->SetActiveObjectsWithTag(false, TAG_M_MENU_MAIN_UI);
    GameManager::GetActiveScene()->SetActiveObjectsWithTag(false, TAG_M_MENU_NEW_GAME_UI);
    m_infoTextObject->active = true;
}

void MainMenuManager::m_SetDefaultMenuUi(){
    // Enable default scene ui - disable rest
    GameManager::GetActiveScene()->SetActiveObjectsWithTag(true, TAG_M_MENU_MAIN_UI);
    GameManager::GetActiveScene()->SetActiveObjectsWithTag(false, TAG_M_MENU_NEW_GAME_UI);
    m_infoTextObject->active = false;
}

void MainMenuManager::m_SetNewGameUi() {
    // Enable new game ui - disable rest
    GameManager::GetActiveScene()->SetActiveObjectsWithTag(false, TAG_M_MENU_MAIN_UI);
    GameManager::GetActiveScene()->SetActiveObjectsWithTag(true, TAG_M_MENU_NEW_GAME_UI);
    m_infoTextObject->active = false;

    m_buffMenu->active = true;
    m_roleMenu->active = false;

    // Reset used tokens count & chosen upgrades vector
    m_usedTokens = 0;
    for(auto& it: m_chosenUpgrades)
        it = 0;
}

void MainMenuManager::m_ApplyNewGameOptions() {
    DataLoader& gameData = GameManager::GetGameData();
    gameData.playerData.role = m_roleMenu->choice;
    gameData.playerData.moveDelay += m_chosenUpgrades[EFFECT_CHANGE_SPEED];
    gameData.playerData.lives += m_chosenUpgrades[EFFECT_CHANGE_LIVES];
    gameData.playerData.attackRange += m_chosenUpgrades[EFFECT_CHANGE_RANGE];
}




