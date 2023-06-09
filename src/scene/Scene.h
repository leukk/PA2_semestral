#pragma once

class GameManager;

#include "SceneObject.h"
#include "../singletons/GameManager.h"
#include "../utils/GameConstants.h"
#include "../scene-objects/MainMenu.h"
#include <vector>
#include <sstream>

using std::vector;
using std::logic_error;

class Scene{
public:
    Scene() = default;
    Scene(const Scene& other) = default;
    ~Scene() = default;

    void Initialize(string sceneConfig);
    void CreateObject(const string& objectParams);
private:
    static string m_GetParamValue(const string& param, const string& objectParams);
public:
private:
    vector<SceneObject*> m_sceneObjects;
};


