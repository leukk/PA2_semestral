#pragma once
#include "../singleton-managers/InputManager.h"
#include "../singleton-managers/GameManager.h"
#include "../scene-base/SceneObject.h"
#include "../scene-objects/Menu.h"
#include <ncurses.h>
#include <vector>
#include <string>

class Menu;

using std::array;

class MainMenuManager : public SceneObject{
public:
    MainMenuManager() = delete;
    explicit MainMenuManager(const SceneObject& sceneObject);
    MainMenuManager(const MainMenuManager& other) = default;
    ~MainMenuManager() override = default;

    /**
     * On scene start override
     *
     * Fetches all necessary dependencies such as menus, text objects..
     */
    void Start() override;
    /**
     * On scene update override
     *
     * Fetches user input and updates menu state accordingly
     * @param updateDeltaMs
     * @return update successful
     */
    bool Update(int updateDeltaMs) override;
    /**
     * On render override
     *
     * Renders main menu text information.
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    /**
     * Enables game information ui, disables rest
     */
    void m_SetInfoUi();
    /**
     * Enables default main menu ui, disables rest
     */
    void m_SetDefaultMenuUi();
    /**
     * Enables new game creation ui, disables rest.
     */
    void m_SetNewGameUi();
    /**
     * Applies game creation changes to current player data state.
     */
    void m_ApplyNewGameOptions();

    enum MENU_STATE{
        MAIN_MENU,
        INFO,
        SELECT_BUFF,
        SELECT_ROLE
    };
    MENU_STATE m_state; /// Menu state

    int m_upgradeTokens; /// Number of upgrade tokens that can be used
    int m_usedTokens; /// Number of used upgrade tokens
    std::vector<int> m_chosenUpgrades; /// Vector of chosen character upgrades

    Menu * m_mainMenu; /// Main menu dependency ptr
    SceneObject * m_infoTextObject; /// Game info object dependency ptr

    Menu * m_buffMenu; /// Buff menu dependency ptr
    Menu * m_roleMenu; /// Role menu dependency ptr
};


