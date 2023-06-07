#pragma once
//#include "SceneObject.h"
#include <vector>
#include <cstdint>
#include <deque>
#include <sstream>

using namespace std;

class Scene{
public:
    Scene() = default;
    ~Scene() = default;

    bool Initialize(string& sceneConfig);
private:
    //vector<SceneObject*> m_sceneObjects;
};


