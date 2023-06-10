#include "GameLoader.h"

GameLoader::GameLoader(Vec2 position, bool active, string objectType, string tags)
    : SceneObject(position, active, std::move(objectType), std::move(tags)){
}

bool GameLoader::Update(double updateDelta) {
    return true;
}

void GameLoader::Render(WINDOW *gameWin, WINDOW *textWin) {
    SceneObject::Render(gameWin, textWin);
}

void GameLoader::Initialize() {
    GameManager& gameManager = GameManager::Get();
    DataLoader* gameData = gameManager.gameData;


    wprintw(gameManager.textWindow, "Enter save file name: ");
}
