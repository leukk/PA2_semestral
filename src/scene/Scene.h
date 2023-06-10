#pragma once

class GameManager;

#include "SceneObject.h"
#include "../managers/GameManager.h"
#include "../utils/GameConstants.h"
#include "../scene-objects/MainMenu.h"
#include "../scene-objects/Text.h"
#include "../scene-objects/GameLoader.h"
#include <vector>
#include <sstream>

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

    vector<SceneObject*> sceneObjects;
};


