#pragma once
#include "../singleton-managers/GameManager.h"
#include "../scene-objects-managers/MainMenuManager.h"
#include "../scene-objects-managers/HubManager.h"
#include "../scene-objects-managers/LevelManager.h"
#include "../scene-objects-managers/BulletManager.h"
#include "../scene-objects/Text.h"
#include "../scene-objects/Menu.h"
#include "../scene-objects/Trigger.h"
#include "../scene-objects/Player.h"
#include "../scene-objects/Enemy.h"
#include "../utils/GameConstants.h"
#include "SceneObject.h"
#include <vector>
#include <sstream>

class GameManager;
class SceneObject;

using std::vector;
using std::logic_error;
using std::to_string;

class Scene{
public:
    Scene() = delete;
    explicit Scene(int sceneIndex);
    Scene(const Scene& other) = default;
    ~Scene();

    void CreateObject(int sceneIndex, int objectIndex);
    [[nodiscard]] SceneObject* GetObjectWithTag(const string& tag) const;
    [[nodiscard]] vector<SceneObject*> GetObjectsWithTag(const string& tag) const;
    void SetActiveObjectsWithTag(bool active, const string& tag);

    vector<SceneObject*> sceneObjects;
};


