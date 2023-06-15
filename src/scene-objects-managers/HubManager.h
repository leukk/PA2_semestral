#pragma once
#include "../singleton-managers/GameManager.h"
#include "../scene-base/SceneObject.h"
#include "../scene-objects/Trigger.h"
#include "../scene-objects/Menu.h"
#include "../structs/Vec2.h"
#include <ncurses.h>
#include <string>
#include <algorithm>

class Trigger;
class Menu;

using std::vector;

class HubManager : public SceneObject {
public:
    HubManager() = delete;
    explicit HubManager(const SceneObject& sceneObject);
    HubManager(const HubManager& other) = default;
    ~HubManager() override = default;

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    enum HUB_STATE{
        NONE,
        SHOP_MENU,
        EQUIP_MENU
    };
    HUB_STATE m_state;

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

