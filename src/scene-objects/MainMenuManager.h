#pragma once
#include "../scene/SceneObject.h"
#include "../scene-objects/Menu.h"
#include "../scene-objects/Text.h"
#include "../managers/InputManager.h"
#include "../managers/GameManager.h"
#include <ncurses.h>
#include <vector>

class Menu;
class Text;

using std::array;

class MainMenuManager : public SceneObject{
public:
    MainMenuManager() = delete;
    MainMenuManager(Vec2 position, bool active, string objectType, string tags);
    MainMenuManager(const MainMenuManager& other) = default;
    ~MainMenuManager() override = default;

    void Start() override;
    bool Update(double updateDelta) override;
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
    MENU_STATE m_state = MAIN_MENU;

    int m_buffTokens = 0;
    int m_usedTokens = 0;
    std::vector<int> m_buffChoices{};

    Menu * m_mainMenu = nullptr;
    SceneObject * m_infoTextObject = nullptr;
    std::vector<SceneObject*> m_menuUi{};

    Menu * m_buffMenu = nullptr;
    Menu * m_roleMenu = nullptr;
    std::vector<SceneObject*> m_newGameUi{};
};


