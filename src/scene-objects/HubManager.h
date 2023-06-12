#pragma once
#include "../scene/SceneObject.h"
#include "Trigger.h"
#include "Menu.h"
#include <ncurses.h>
#include <algorithm>

class Trigger;
class Menu;

using std::vector;

class HubManager : public SceneObject {
public:
    HubManager() = delete;
    HubManager(const HubManager& other) = default;
    HubManager(Vec2 position, bool active, string objectType, string tags, Vec2 playerSpawnPos);
    ~HubManager() override = default;

    void Start() override;
    bool Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    enum HUB_STATE{
        NONE,
        SHOP_MENU,
        EQUIP_MENU
    };
    HUB_STATE m_state = NONE;

    Vec2 m_playerSpawnPos = Vec2::Zero();
    SceneObject * m_player = nullptr;

    Menu * m_shopMenu = nullptr;
    Menu * m_equipMenu = nullptr;

    Trigger * m_buyTrigger = nullptr;
    Trigger * m_equipTrigger = nullptr;
    Trigger * m_exitTrigger = nullptr;
    Trigger * m_levelTrigger = nullptr;

    int m_coins = 0;
    int m_itemPrice = 0;
    int m_nextLevelIndex = 0;
    int m_equippedItemsLimit = 0;
    vector<int> m_equippedItems{};
    vector<int> m_ownedItems{};

    bool m_isEquipped = false;
    bool m_canEquip = false;
    bool m_isOwned = false;
    bool m_canPurchase = false;
};

