#pragma once
#include "../managers/GameManager.h"
#include "../managers/InputManager.h"
#include "../utils/DataLoader.h"
#include "../scene/SceneObject.h"


class GameLoader : public SceneObject{
public:
    GameLoader() = delete;
    GameLoader(Vec2 position, bool active, string objectType, string tags);
    GameLoader(const GameLoader& other) = default;
    ~GameLoader() override = default;

    void Initialize() override;
    bool Update(double updateDelta) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;

private:
    string m_saveFileName;
};


