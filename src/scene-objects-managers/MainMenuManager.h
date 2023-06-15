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

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    void m_SetInfoUi();
    void m_SetMainUi();
    void m_SetNewGameUi();
    void m_ApplyNewGameOptions();

    enum MENU_STATE{
        MAIN_MENU,
        INFO,
        SELECT_BUFF,
        SELECT_ROLE
    };
    MENU_STATE m_state;

    int m_buffTokens;
    int m_usedTokens;
    std::vector<int> m_buffChoices;

    Menu * m_mainMenu;
    SceneObject * m_infoTextObject;

    Menu * m_buffMenu;
    Menu * m_roleMenu;

    Vec2 m_playerSpawnPos;
};


