#include "Scene.h"

void Scene::Initialize(string sceneConfig) {
    string objectParams;
    size_t nextObjectPos, firstParamPos;
    while (!sceneConfig.empty()){
        // Find next scene object to set up, else end initialization
        nextObjectPos = sceneConfig.find(CONF_OBJECT_DELIM);
        if(nextObjectPos == string::npos)
            return;

        objectParams.clear(); // Clear last objects params

        // Find first parameter of next object
        firstParamPos = sceneConfig.find(CONF_PARAM_DELIM, nextObjectPos);
        if(firstParamPos == string::npos)
            throw logic_error("Invalid config: No parameters following object delimiter\n");

        // Find where following scene object begins (param range) & copy param part
        nextObjectPos = sceneConfig.find(CONF_OBJECT_DELIM, firstParamPos);
        if(nextObjectPos == string::npos)
            objectParams = sceneConfig.substr(firstParamPos);
        else
            objectParams = sceneConfig.substr(firstParamPos, nextObjectPos - firstParamPos);

        // Create object

        // Remove processed part from sceneConfig string or break if no more objects in config
        if(nextObjectPos == string::npos)
            return;
        sceneConfig = sceneConfig.substr(nextObjectPos);
    }
}

void Scene::CreateObject(string objectParams) {

}
