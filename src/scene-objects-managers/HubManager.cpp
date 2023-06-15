#include "HubManager.h"

#include <utility>

HubManager::HubManager(const SceneObject& sceneObject) :
        SceneObject(sceneObject),
        m_state(NONE),
        m_playerInitialPos(Vec2::Zero()),
        m_player(nullptr), m_shopMenu(nullptr), m_equipMenu(nullptr),
        m_buyTrigger(nullptr), m_equipTrigger(nullptr), m_exitTrigger(nullptr), m_levelTrigger(nullptr),
        m_itemPrice(0), m_equippedItemsLimit(0), m_isEquipped(false), m_canEquip(false), m_isOwned(false),
        m_canPurchase(false) {
}

void HubManager::Start() {
    DataLoader& gameData = GameManager::GetGameData();
    Scene* gameScene = GameManager::GetActiveScene();
    ostringstream missingObjects;

    // Get hub dependencies
    m_player = gameScene->GetObjectWithTag(TAG_PLAYER);
    if(!m_player)
        missingObjects << TAG_PLAYER;
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

    // Throw if dependencies missing
    if(!missingObjects.str().empty())
        throw invalid_argument(" Hub manager requires objects with following tags:\n" + missingObjects.str());

    // Get equipped items limit from config data
    m_equippedItemsLimit = gameData.ConfigGetNumParam(SHARED_DATA, SHARED_DATA, PARAM_ITEM_EQUIP_LIMIT);
    if(!m_equippedItemsLimit)
        throw invalid_argument(" Item equip limit not defined or set to 0");

    m_playerInitialPos = m_player->position;
}

bool HubManager::Update(int updateDeltaMs) {
    (void)updateDeltaMs;
    DataLoader& gameData = GameManager::GetGameData();
    Scene * activeScene = GameManager::GetActiveScene();

    // Player is entering a level
    if(m_levelTrigger->triggered){
        // Try load next level scene
        try{
            m_player->position = m_playerInitialPos;
            if(gameData.playerData.nextLevelIndex >= (int)gameData.ConfigLevels().size()){
                GameManager::ShowError(" No more levels\n");
                return false;
            }
            GameManager::LoadScene(gameData.ConfigLevels()[gameData.playerData.nextLevelIndex].sceneIndex);
            return false;
        }
        catch (exception& e){
            GameManager::ShowError(" Failed to enter quest scene\n" + string(e.what()));
        }
        return false;
    }

    // Player is leaving game
    if(m_exitTrigger->triggered){
        // Save player data & go back to main menu
        m_player->position = m_playerInitialPos;
        gameData.SavePlayerData();
        gameData.UnsetPlayerDataFilePath();
        GameManager::LoadScene(GameManager::GetMenuSceneIndex());
        return false;
    }

    // Player entering buy menu
    if(m_buyTrigger->triggered && m_state==NONE && InputManager::GetKeyDown(KEY_SPACE)){
        m_shopMenu->options.clear();
        for(auto& it : gameData.ConfigItems())
            m_shopMenu->options.push_back(it.title);
        // Switch ui to buy menu
        activeScene->SetActiveObjectsWithTag(true, TAG_HUB_SHOP_UI);
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_DEFAULT_UI);
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_EQUIP_UI);
        m_state = SHOP_MENU;
        return false;
    }

    // Player entering equip menu
    if(m_equipTrigger->triggered && m_state==NONE && InputManager::GetKeyDown(KEY_SPACE)){
        // Update equip menu options based on owned items
        m_equipMenu->options.clear();
        for(auto& it : gameData.playerData.ownedItems)
            m_equipMenu->options.push_back(gameData.ConfigItems()[it].title);
        // Switch ui to equip menu
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_SHOP_UI);
        activeScene->SetActiveObjectsWithTag(false, TAG_HUB_DEFAULT_UI);
        activeScene->SetActiveObjectsWithTag(true, TAG_HUB_EQUIP_UI);
        m_state = EQUIP_MENU;
        return false;
    }

    // Player in shop menu
    if(m_state == SHOP_MENU){
        // Player leaving shop menu - enable default ui
        if(InputManager::GetKeyDown(KEY_SPACE)){
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_SHOP_UI);
            activeScene->SetActiveObjectsWithTag(true, TAG_HUB_DEFAULT_UI);
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_EQUIP_UI);
            m_state = NONE;
            return false;
        }

        // Return if no items defined in config
        if(gameData.ConfigItems().empty())
            return true;

        // Find currently selected item & get price, can purchase / is owned info
        auto itemIndexIt = std::find(gameData.playerData.ownedItems.begin(), gameData.playerData.ownedItems.end(),
                                     (int)m_shopMenu->choice);
        m_isOwned = itemIndexIt != gameData.playerData.ownedItems.end();

        m_itemPrice = gameData.ConfigItems()[m_shopMenu->choice].price;
        m_canPurchase = gameData.playerData.coins >= m_itemPrice;

        // Purchase on right key
        if(!m_isOwned && m_canPurchase && InputManager::GetKeyDown(KEY_RIGHT)){
            gameData.playerData.coins -= m_itemPrice;
            gameData.playerData.ownedItems.push_back(m_shopMenu->choice);
        }

        // Sell on left key
        if(m_isOwned && InputManager::GetKeyDown(KEY_LEFT)){
            // Remove from equippedIt items
            auto equippedIt = std::find(gameData.playerData.equippedItems.begin(), gameData.playerData.equippedItems.end(),
                                        *itemIndexIt);
            if (equippedIt != gameData.playerData.equippedItems.end())
                gameData.playerData.equippedItems.erase(equippedIt);

            // Remove from bought items & get back half price
            gameData.playerData.coins += m_itemPrice / 2;
            gameData.playerData.ownedItems.erase(itemIndexIt);
        }
    }

    // Player in equip menu
    if(m_state == EQUIP_MENU){
        // Player leaving equip menu - enable default ui
        if(InputManager::GetKeyDown(KEY_SPACE)){
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_SHOP_UI);
            activeScene->SetActiveObjectsWithTag(true, TAG_HUB_DEFAULT_UI);
            activeScene->SetActiveObjectsWithTag(false, TAG_HUB_EQUIP_UI);
            m_state = NONE;
            return false;
        }

        // Return if no owned items
        if(m_equipMenu->options.empty())
            return true;

        // Find equipped item & isEquipped info
        auto itemEquippedIt = std::find(gameData.playerData.equippedItems.begin(), gameData.playerData.equippedItems.end(),
                                        gameData.playerData.ownedItems[m_equipMenu->choice]);
        m_isEquipped = itemEquippedIt != gameData.playerData.equippedItems.end();

        // Unequip on left key
        if(m_isEquipped && InputManager::GetKeyDown(KEY_LEFT)){
            gameData.playerData.equippedItems.erase(itemEquippedIt);
        }

        // Equip on right key
        m_canEquip = (int)gameData.playerData.equippedItems.size() < m_equippedItemsLimit;
        if(m_canEquip && !m_isEquipped && InputManager::GetKeyDown(KEY_RIGHT)){
            gameData.playerData.equippedItems.push_back(gameData.playerData.ownedItems[m_equipMenu->choice]);
        }
    }

    return true;
}

void HubManager::Render(WINDOW *gameWin, WINDOW *textWin) {
    (void)gameWin;
    DataLoader& gameData = GameManager::GetGameData();

    // Render default hub text - level info
    if(m_state == NONE){
        if(m_buyTrigger->triggered)
            wprintw(textWin, " Enter shop by pressing 'SPACE'\n");
        else if(m_equipTrigger->triggered)
            wprintw(textWin, " Enter inventory by pressing 'SPACE'\n");
        else{
            const vector<Item>& items = gameData.ConfigItems();
            wprintw(textWin, " Equipped items: ");
            for(auto index: gameData.playerData.equippedItems)
                wprintw(textWin, " %s ", items[index].title.c_str());

            const Level& nextLevel = gameData.ConfigLevels()[gameData.playerData.nextLevelIndex];
            wprintw(textWin, "\n Next level [%d]: %s\n\n %s", gameData.playerData.nextLevelIndex,
                    nextLevel.title.c_str(), nextLevel.description.c_str());
        }
    }

    // Render shop text - item / purchasing info
    if(m_state == SHOP_MENU){
        wprintw(textWin, " SHOP: Buy by pressing 'RIGHT', sell by pressing 'LEFT'\n");
        if(m_isOwned)
            wprintw(textWin, " Item owned, can be sold for: %d\n", m_itemPrice/2);
        else{
            wprintw(textWin, " Item not owned, cost: %d, coins: %d", m_itemPrice, gameData.playerData.coins);
            if(m_canPurchase)
                wprintw(textWin, " - purchase by pressing 'RIGHT'\n");
            else
                wprintw(textWin, " - not enough coins to purchase\n");
        }
        wprintw(textWin, " Exit by pressing 'SPACE'\n");
    }

    // Render equip text - item equipping info
    if(m_state == EQUIP_MENU){
        wprintw(textWin, " INVENTORY: 'RIGHT' to equip, 'LEFT' to unequip, empty slots: %zu\n",
                m_equippedItemsLimit-gameData.playerData.equippedItems.size());
        wprintw(textWin, " Equipped: %s\n", m_isEquipped ? "true" : "false");
        wprintw(textWin, " Exit by pressing 'SPACE'\n");
    }
}
