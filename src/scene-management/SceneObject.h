#pragma once
#include "Scene.h"
#include <cstdint>
#include <string>

using namespace std;

class SceneObject {
public:
    SceneObject() = default;
    virtual ~SceneObject() = default;
    virtual void Initialize() = 0;
    virtual void Update(double updateDelta) = 0;
    virtual string OnSave() = 0;
    virtual bool OnLoad(string config) = 0;
};



