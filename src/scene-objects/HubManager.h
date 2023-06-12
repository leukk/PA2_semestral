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

    Vec2 m_playerSpawnPos;
    SceneObject * m_player;

    Menu * m_shopMenu;
    Menu * m_equipMenu;

    Trigger * m_buyTrigger;
    Trigger * m_equipTrigger;
    Trigger * m_exitTrigger;
    Trigger * m_levelTrigger;

    int m_itemPrice;
    int m_equippedItemsLimit;

    bool m_isEquipped;
    bool m_canEquip;
    bool m_isOwned;
    bool m_canPurchase;
};

