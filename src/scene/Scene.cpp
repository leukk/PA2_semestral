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
        firstParamPos = sceneConfig.find(CONF_PARAM_START_DELIM, nextObjectPos);
        if(firstParamPos == string::npos)
            throw logic_error("No parameters following object delimiter\n");

        // Find where following scene object begins (param range) & copy param part
        nextObjectPos = sceneConfig.find(CONF_OBJECT_DELIM, firstParamPos);
        if(nextObjectPos == string::npos)
            objectParams = sceneConfig.substr(firstParamPos);
        else
            objectParams = sceneConfig.substr(firstParamPos, nextObjectPos - firstParamPos);

        // Create object
        CreateObject(objectParams);

        // Remove processed part from sceneConfig string or break if no more objects in config
        if(nextObjectPos == string::npos)
            return;
        sceneConfig = sceneConfig.substr(nextObjectPos);
    }
}

void Scene::CreateObject(const string& objectParams) {
    string typeParamString = m_GetParamValue("--type", objectParams);
    auto typeParam = static_cast<OBJECT_TYPE>(stoi(typeParamString));

    if(typeParam == NONE)
        throw logic_error("Invalid object type of " + typeParamString);

    // Retrieve parameters from config string & create object
    SceneObject* newObject = nullptr;
    string tags = m_GetParamValue("--tags", objectParams);

    if(typeParam == TEXT){

    }
    else if(typeParam == LOGO){

    }
    else if(typeParam == MAIN_MENU){
        string name = m_GetParamValue("--name", objectParams);
        string description = m_GetParamValue("--description", objectParams);
        newObject = new MainMenu(typeParam, tags, name, description);
    }

    if(!newObject)
        throw logic_error("Object not created, failed to match type or allocate\n");

    // Add created object to "active" objects vec
    m_sceneObjects.push_back(newObject);

    // m_Initialize object & call start if scene is already loaded
    newObject->Initialize();
    if(GameManager::Get().GetGameState() == RUNNING)
        newObject->Start();
}

string Scene::m_GetParamValue(const string &param, const string &objectParams) {
    // Finds parameter position in config - returns empty if none
    size_t paramPos = objectParams.find(param);
    if(paramPos == string::npos)
        return {};

    // Move paramPos "in front" of value following parameter
    paramPos += param.size();

    size_t valueStart = objectParams.find(CONF_VALUE_DELIM, paramPos);
    if(valueStart == string::npos)
        throw logic_error("No value delimiters following parameter\n");

    size_t valueEnd = objectParams.find(CONF_VALUE_DELIM,valueStart+1);
    if(valueEnd == string::npos)
        throw logic_error("No ending value delimiter found\n");

    return objectParams.substr(valueStart+1, valueEnd-valueStart-1);
}



