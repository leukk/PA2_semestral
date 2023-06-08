#pragma once
#include "../GameConstants.h"
#include "SceneObject.h"
#include <vector>
#include <cstdint>
#include <deque>
#include <sstream>

using namespace std;

class Scene{
public:
    Scene() = default;
    ~Scene() = default;

    void Initialize(string sceneConfig);
    void CreateObject(string objectParams);
private:
    vector<SceneObject*> m_sceneObjects;
};


