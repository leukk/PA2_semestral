#include "Scene.h"

 Scene::Scene(int sceneIndex) {
    // Get game data & number of objects in given sceneIndex
    DataLoader* gameData = GameManager::Get().gameData;
    int sceneObjCount = (int)gameData->ConfigObjectCount(sceneIndex);

    // Initialize each object by its prefix
    for (int objId = 0; objId < sceneObjCount; objId++)
        CreateObject(sceneIndex, objId);
}

Scene::~Scene() {
    for (SceneObject* ptr : sceneObjects) {
        delete ptr;
    }
}

void Scene::CreateObject(int sceneIndex, int objectIndex) {
    DataLoader* gameData = GameManager::Get().gameData;

    // Retrieve non string parameter sources
    string positionString = gameData->ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_POSITION);
    string activeString = gameData->ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_ACTIVE);

    // Set or retrieve base object parameters
    Vec2 position = positionString.empty() ? Vec2::Zero() : Vec2(positionString);
    bool active = !(activeString == "false" || activeString == "0");
    string objectType = gameData->ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_TYPE);
    string tags = gameData->ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_TAGS);

    // Throw if no object type specified
    if(objectType.empty())
        throw logic_error(" Trying to create object with empty object type\n");

    SceneObject* newObject = nullptr;
    if(objectType == OBJECT_MAIN_MENU){
        newObject = new MainMenu(position, active, objectType, tags);
    }
    else if(objectType == OBJECT_TEXT){
        string contents = gameData->ConfigGetParam(sceneIndex, objectIndex, "--contents");
        newObject = new Text(position, active, objectType, tags, contents);
    }
    else if(objectType == OBJECT_PLAYER_CREATOR){
        newObject = new GameLoader(position, active, objectType, tags);
    }

    if(!newObject)
        throw logic_error(" Object not created, failed to match type or allocate for type: " + objectType + "\n");

    // Add created object to "active" objects vec
    sceneObjects.push_back(newObject);

    // m_Initialize object & call start if scene is already loaded
    newObject->Initialize();
    if(GameManager::Get().GetGameState() == RUNNING)
        newObject->Start();
}

SceneObject* Scene::GetObjectWithTag(const string &tag) const {
    for (SceneObject* ptr : sceneObjects) {
        if(ptr->HasTag(tag))
            return ptr;
    }
    return nullptr;
}




