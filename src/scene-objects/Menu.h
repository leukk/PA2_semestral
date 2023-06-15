#pragma once
#include "../singleton-managers/InputManager.h"
#include "../scene-base/DisplayObject.h"
#include <vector>
#include <sstream>
#include <string>

using std::vector;
using std::string;
using std::istringstream;

/**
 * Menu: inherits DisplayObject
 *
 * Prints contents to gameWindow as a menu.
 * Individual options are separated by spaces
 * @note If position left as (0,0) - centers itself to the middle of screen.
 */
class Menu : public DisplayObject{
public:
    Menu() = delete;
    explicit Menu(const DisplayObject& displayObj);
    Menu(const Menu& other) = default;
    ~Menu() override = default;

    /**
     * Start override
     *
     * Parses content sting to options vector.
     * Options are divided by spaces
     */
    void Start() override;
    /**
     * Update override
     *
     * Updates selected item based on user input.
     * @param updateDeltaMs
     * @return update success
     */
    bool Update(int updateDeltaMs) override;
    /**
     * Render override
     *
     * Renders menu to game window.
     * Highlights & adds arrows to selected option.
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    int choice; /// Currently selected option
    bool selectable; /// Menu reacts to user input
    vector<string> options; /// Individual options from contents string
};

