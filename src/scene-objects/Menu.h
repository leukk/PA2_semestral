#pragma once
#include "../singleton-managers/InputManager.h"
#include "../scene-base/DisplayObject.h"
#include <vector>
#include <sstream>
#include <string>

using std::vector;
using std::string;
using std::istringstream;

class Menu : public DisplayObject{
public:
    Menu() = delete;
    explicit Menu(const DisplayObject& displayObj);
    Menu(const Menu& other) = default;
    ~Menu() override = default;

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

    int choice;
    bool selectable;
    vector<string> options;
};

