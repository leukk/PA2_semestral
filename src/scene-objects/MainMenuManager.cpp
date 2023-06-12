#include "MainMenuManager.h"


MainMenuManager::MainMenuManager(Vec2 position, bool active, string objectType, string tags)
    : SceneObject(position, active, std::move(objectType), std::move(tags)){
}

void MainMenuManager::Start() {
    Scene* gameScene = GameManager::GetActiveScene();
    ostringstream missingObjects;

    m_menuUi = gameScene->GetObjectsWithTag(TAG_M_MENU_MAIN_UI);
    if(m_menuUi.empty())
        missingObjects << TAG_M_MENU_MAIN_UI;
    m_mainMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_M_MENU_MENU_OBJ));
    if(!m_mainMenu)
        missingObjects << TAG_M_MENU_MENU_OBJ;
    m_infoTextObject = gameScene->GetObjectWithTag(TAG_M_MENU_INFO_OBJ);
    if(!m_infoTextObject)
        missingObjects << TAG_M_MENU_INFO_OBJ;

    m_newGameUi = gameScene->GetObjectsWithTag(TAG_M_MENU_NEW_GAME_UI);
    if(m_newGameUi.empty())
        missingObjects << TAG_M_MENU_NEW_GAME_UI;
    m_buffMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_M_MENU_BUFF_MENU_OBJ));
    if(!m_buffMenu)
        missingObjects << TAG_M_MENU_BUFF_MENU_OBJ;
    m_roleMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_M_MENU_ROLE_MENU_OBJ));
    if(!m_roleMenu)
        missingObjects << TAG_M_MENU_ROLE_MENU_OBJ;

    if(!missingObjects.str().empty())
        throw invalid_argument("Main menu manager required objects with following tags:\n" + missingObjects.str());

    if(m_buffMenu->options.size() != 3)
        throw logic_error("Buff menu / role menu must both have 3 options\n");

    m_buffTokens = GameManager::GetGameData().ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_CREATE_BUFF_TOKENS);
    m_buffChoices.clear();
    for(size_t i = 0; i < m_buffMenu->options.size(); i++)
        m_buffChoices.push_back(0);
}

bool MainMenuManager::Update(double updateDelta) {
    (void) updateDelta;
    DataLoader& gameData = GameManager::GetGameData();

    if(m_state == MAIN_MENU){
        if(InputManager::GetKeyDown(KEY_RIGHT)){
            switch (m_mainMenu->choice) {
                case 0:
                    try{
                        gameData.SetPlayerDataFilePath();
                        gameData.SetDefaultPlayerStats();
                        gameData.SavePlayerData();
                        m_state = SELECT_BUFF;
                        m_SetNewGameUi();
                    }
                    catch (exception& e){
                        GameManager::ShowError(e.what());
                    }
                    return false;
                case 1:
                    try{
                        gameData.SetPlayerDataFilePath();
                        gameData.LoadPlayerData();
                        GameManager::LoadScene(GameManager::GetHubSceneIndex());
                    }
                    catch (exception& e){
                        GameManager::ShowError(e.what());
                    }
                    return false;
                case 2:
                    m_state = INFO;
                    m_SetInfoUi();
                    return false;
                case 3:
                    GameManager::ExitGame();
                    return false;
            }
        }
        return true;
    }

    if(m_state == INFO && InputManager::GetKeyDown(KEY_LEFT)){
        m_state = MAIN_MENU;
        m_SetMainUi();
        return false;
    }

    if(m_state == SELECT_BUFF){
        if(InputManager::GetKeyDown(KEY_RIGHT) && m_usedTokens < m_buffTokens){
            m_buffChoices[m_buffMenu->choice] += 1;
            m_usedTokens++;
        }
        if(InputManager::GetKeyDown(KEY_LEFT) && m_buffChoices[m_buffMenu->choice] > 0){
            m_buffChoices[m_buffMenu->choice] -= 1;
            m_usedTokens--;
        }
        if(m_usedTokens == m_buffTokens){
            m_state = SELECT_ROLE;
            m_buffMenu->active = false;
            m_roleMenu->active = true;
            return false;
        }
        return true;
    }

    if(m_state == SELECT_ROLE){
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

    if(m_state == SELECT_BUFF || m_state == SELECT_ROLE)
        wprintw(textWin, " Creating new game, save file: %s\n", GameManager::GetGameData().PlayerDataPath().c_str());
    if(m_state == SELECT_BUFF){
        wprintw(textWin, " Upgrade your character abilities, %d remaining\n", m_buffTokens-m_usedTokens);
        for (size_t i = 0; i < m_buffMenu->options.size(); ++i)
            wprintw(textWin, " %s: %d ", m_buffMenu->options[i].c_str(), m_buffChoices[i]);
    }
    if(m_state == SELECT_ROLE)
        wprintw(textWin, " Select your character role\n");
}

void MainMenuManager::m_SetInfoUi() {
    for (auto it: m_menuUi) {
        it->active = false;
    }
    for (auto it: m_newGameUi) {
        it->active = false;
    }
    m_infoTextObject->active = true;
}

void MainMenuManager::m_SetMainUi(){
    for (auto it: m_menuUi) {
        it->active = true;
    }
    for (auto it: m_newGameUi) {
        it->active = false;
    }
    m_infoTextObject->active = false;
}

void MainMenuManager::m_SetNewGameUi() {
    for (auto it: m_menuUi) {
        it->active = false;
    }
    for (auto it: m_newGameUi) {
        it->active = true;
    }
    m_infoTextObject->active = false;

    m_buffMenu->active = true;
    m_roleMenu->active = false;

    m_usedTokens = 0;
    for(auto& it: m_buffChoices)
        it = 0;
}

void MainMenuManager::m_ApplyNewGameOptions() {
    DataLoader& gameData = GameManager::GetGameData();
    gameData.playerData.role = m_roleMenu->choice;
    gameData.playerData.speed += m_buffChoices[EFFECT_CHANGE_SPEED];
    gameData.playerData.lives += m_buffChoices[EFFECT_CHANGE_LIVES];
    gameData.playerData.range += m_buffChoices[EFFECT_CHANGE_RANGE];
}




