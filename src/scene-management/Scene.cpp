#include "Scene.h"

#define SOBJ_CONF_DELIM "#sobj"

bool Scene::Initialize(string &sceneConfig) {
    string configBuffer;
    istringstream configStream(sceneConfig);
    while (configStream.good()){
        configStream >> configBuffer;

    }
}
