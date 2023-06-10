#pragma once

class GameManager;

#include "SceneObject.h"
#include "../singletons/GameManager.h"
#include "../utils/GameConstants.h"
#include "../scene-objects/MainMenu.h"
#include "../scene-objects/Text.h"
#include <vector>
#include <sstream>

using std::vector;
using std::logic_error;
using std::to_string;

class Scene{
public:
    Scene() = delete;
    explicit Scene(int sceneId);
    Scene(const Scene& other) = default;
    ~Scene();

    void CreateObject(int sceneIndex, int objectIndex);

    vector<SceneObject*> sceneObjects;
};


