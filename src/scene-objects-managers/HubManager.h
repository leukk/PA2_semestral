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

    /**
     * On scene start override
     *
     * Fetches all necessary dependencies such as player, menus, etc.
     */
    void Start() override;
    /**
     * On scene update override
     *
     * Fetches user input and updates hub state accordingly
     * @param updateDeltaMs
     * @return update successful
     */
    bool Update(int updateDeltaMs) override;
    /**
     * On render override
     *
     * Renders hub text information.
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    /**
     * Hub state
     */
    enum HUB_STATE{
        NONE,
        SHOP_MENU,
        EQUIP_MENU
    };
    HUB_STATE m_state; /// Current hub state

    Vec2 m_playerInitialPos; /// Initial player position for respawning
    SceneObject * m_player; /// Player dependency pointer

    Menu * m_shopMenu; /// Shop menu dependency pointer
    Menu * m_equipMenu; /// Equip menu dependency pointer

    Trigger * m_buyTrigger; /// Buy trigger dependency pointer
    Trigger * m_equipTrigger; /// Equip trigger dependency pointer
    Trigger * m_exitTrigger; /// Exit trigger dependency pointer
    Trigger * m_levelTrigger; /// Enter level trigger dependency pointer

    int m_itemPrice; /// Selected item price
    int m_equippedItemsLimit; /// Limit of equipped items

    bool m_isEquipped; /// Item is equipped
    bool m_canEquip; /// Item can be equipped
    bool m_isOwned; /// Item is owned
    bool m_canPurchase; /// Item can be purchased
};

