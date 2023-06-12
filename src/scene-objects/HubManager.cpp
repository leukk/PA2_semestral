#include "HubManager.h"

HubManager::HubManager(Vec2 position, bool active, string objectType, string tags, Vec2 playerSpawnPos) :
        SceneObject(position, active, std::move(objectType), std::move(tags)){
}

void HubManager::Start() {
    DataLoader& gameData = GameManager::GetGameData();
    Scene* gameScene = GameManager::GetActiveScene();
    ostringstream missingObjects;

    m_player = gameScene->GetObjectWithTag(TAG_HUB_PLAYER);
    if(!m_player)
        missingObjects << TAG_HUB_PLAYER;
    m_buyTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_HUB_BUY_TRIGGER));
    if(!m_buyTrigger)
        missingObjects << TAG_HUB_BUY_TRIGGER;
    m_equipTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_HUB_EQUIP_TRIGGER));
    if(!m_equipTrigger)
        missingObjects << TAG_HUB_EQUIP_TRIGGER;
    m_exitTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_HUB_EXIT_TRIGGER));
    if(!m_exitTrigger)
        missingObjects << TAG_HUB_EXIT_TRIGGER;
    m_levelTrigger = dynamic_cast<Trigger*>(gameScene->GetObjectWithTag(TAG_HUB_LEVEL_TRIGGER));
    if(!m_levelTrigger)
        missingObjects << TAG_HUB_LEVEL_TRIGGER;
    m_shopMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_HUB_SHOP_MENU));
    if(!m_shopMenu)
        missingObjects << TAG_HUB_SHOP_MENU;
    m_equipMenu = dynamic_cast<Menu*>(gameScene->GetObjectWithTag(TAG_HUB_EQUIP_MENU));
    if(!m_equipMenu)
        missingObjects << TAG_HUB_EQUIP_MENU;

    if(!missingObjects.str().empty())
        throw invalid_argument(" Hub manager requires objects with following tags:\n" + missingObjects.str());

    m_equippedItemsLimit = gameData.ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_ITEM_EQUIP_LIMIT);
    if(!m_equippedItemsLimit)
        throw invalid_argument(" Item equip limit not defined or set to 0");

    m_equippedItems = gameData.PlayerDataGetNums(PLAYER_DATA_EQUIPPED_ITEMS);
    m_ownedItems = gameData.PlayerDataGetNums(PLAYER_DATA_OWNED_ITEMS);
    m_coins = gameData.PlayerDataGetNum(PLAYER_DATA_COINS);

    m_shopMenu->options.clear();
    for(auto& it : gameData.ConfigItems())
        m_shopMenu->options.push_back(it.title);

    m_equipMenu->options.clear();
    for(auto& it : m_ownedItems)
        m_shopMenu->options.push_back(gameData.ConfigItems()[it].title);
}

bool HubManager::Update(double updateDelta) {
    (void)updateDelta;
    DataLoader& gameData = GameManager::GetGameData();
    Scene * activeScene = GameManager::GetActiveScene();

    if(m_levelTrigger->triggered){
        try{
            m_player->position = m_playerSpawnPos;
            int nextLevelIndex = gameData.PlayerDataGetNum(PLAYER_DATA_NEXT_LEVEL);
            if(nextLevelIndex >= (int)gameData.ConfigLevels().size()){
                GameManager::ShowError(" No more quests\n");
                return false;
            }
            GameManager::LoadScene(gameData.ConfigLevels()[nextLevelIndex].sceneIndex);
            return false;
        }
        catch (exception& e){
            GameManager::ShowError(" Failed to enter quest scene\n" + string(e.what()));
        }
        return false;
    }
    if(m_exitTrigger->triggered){
        m_player->position = m_playerSpawnPos;
        gameData.SavePlayerData();
        gameData.SetDefaultPlayerStats();
        GameManager::LoadScene(GameManager::GetMenuSceneIndex());
        return false;
    }
    if(m_buyTrigger->triggered && InputManager::GetKeyDown(KEY_SPACE)){
        activeScene->SetActiveObjectsWithTag(true, TAG_HUB_SHOP_UI);
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_DEFAULT_UI);
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_EQUIP_UI);
        m_state = SHOP_MENU;
        return false;
    }
    if(m_equipTrigger->triggered && InputManager::GetKeyDown(KEY_SPACE)){
        m_equipMenu->options.clear();
        for(auto& it : m_ownedItems)
            m_shopMenu->options.push_back(gameData.ConfigItems()[it].title);
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_SHOP_UI);
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_DEFAULT_UI);
        activeScene->SetActiveObjectsWithTag(true, TAG_HUB_EQUIP_UI);
        m_state = EQUIP_MENU;
        return false;
    }

    if(m_state == SHOP_MENU){
        if(InputManager::GetKeyDown(KEY_BACKSPACE)){
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_SHOP_UI);
            activeScene->SetActiveObjectsWithTag(true, TAG_HUB_DEFAULT_UI);
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_EQUIP_UI);
            m_state = NONE;
            return false;
        }

        auto itemIndexIt = std::find(m_ownedItems.begin(), m_ownedItems.end(), (int)m_shopMenu->choice);
        m_isOwned = itemIndexIt != m_ownedItems.end();

        m_itemPrice = gameData.ConfigItems()[m_shopMenu->choice].price;
        m_canPurchase = m_coins >= m_itemPrice;

        if(!m_isOwned && m_canPurchase && InputManager::GetKeyDown(KEY_RIGHT)){
            m_coins -= m_itemPrice;
            gameData.PlayerDataSetNum(PLAYER_DATA_COINS, m_coins);
            m_ownedItems.push_back(m_shopMenu->choice);
            gameData.PlayerDataSetNums(PLAYER_DATA_OWNED_ITEMS, m_ownedItems);
        }

        if(m_isOwned && InputManager::GetKeyDown(KEY_LEFT)){
            m_coins += m_itemPrice / 2;
            gameData.PlayerDataSetNum(PLAYER_DATA_COINS, m_coins);
            m_ownedItems.erase(itemIndexIt);
            gameData.PlayerDataSetNums(PLAYER_DATA_OWNED_ITEMS, m_ownedItems);
        }
    }

    if(m_state == EQUIP_MENU){
        if(InputManager::GetKeyDown(KEY_BACKSPACE)){
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_SHOP_UI);
            activeScene->SetActiveObjectsWithTag(true, TAG_HUB_DEFAULT_UI);
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_EQUIP_UI);
            m_state = NONE;
            return false;
        }

        auto itemEquippedIt = std::find(m_equippedItems.begin(), m_equippedItems.end(), m_ownedItems[m_equipMenu->choice]);
        m_isEquipped = itemEquippedIt != m_equippedItems.end();

        if(m_isEquipped && InputManager::GetKeyDown(KEY_LEFT)){
            m_equippedItems.erase(itemEquippedIt);
        }

        m_canEquip = (int)m_equippedItems.size() < m_equippedItemsLimit;
        if(m_canEquip && InputManager::GetKeyDown(KEY_RIGHT)){
            m_equippedItems.push_back(m_ownedItems[m_equipMenu->choice]);
        }
    }

    return true;
}

void HubManager::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)gameWin;
    DataLoader& gameData = GameManager::GetGameData();

    if(m_state == NONE){
        if(m_buyTrigger->triggered)
            wprintw(textWin, " Enter shop by pressing 'SPACE'\n");
        else if(m_equipTrigger->triggered)
            wprintw(textWin, " Enter inventory by pressing 'SPACE'\n");
        else{
            const vector<Item>& items = gameData.ConfigItems();
            wprintw(textWin, " Equipped items: ");
            for(auto index: m_equippedItems)
                wprintw(textWin, " %s ", items[index].title.c_str());

            const Level& nextLevel = gameData.ConfigLevels()[m_nextLevelIndex];
            wprintw(textWin, " Next level [%d]: %s\n\n %s", m_nextLevelIndex,
                    nextLevel.title.c_str(), nextLevel.description.c_str());
        }
    }

    if(m_state == SHOP_MENU){
        if(m_isOwned)
            wprintw(textWin, " SHOP: Item owned, sell by pressing 'LEFT' for half original price\n");
        else{
            wprintw(textWin, " SHOP: Item not owned, cost: %d, coins: %d", m_itemPrice, m_coins);
            if(m_canPurchase)
                wprintw(textWin, " - purchase by pressing 'RIGHT'\n");
            else
                wprintw(textWin, " - not enough to purchase\n");
        }
        wprintw(textWin, " Exit by pressing 'BACKSPACE'\n");
    }

    if(m_state == EQUIP_MENU){
        wprintw(textWin, " INVENTORY: 'RIGHT' to equip, 'LEFT' to unequip, empty slots: %zu\n", m_equippedItemsLimit-m_equippedItems.size());
        wprintw(textWin, " Equipped: %s\n", m_isEquipped ? "true" : "false");
        wprintw(textWin, " Exit by pressing 'BACKSPACE'\n");
    }
}
