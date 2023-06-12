#include "Scene.h"

Scene::Scene(int sceneIndex) {
    // Get number of objects in given sceneIndex
    int sceneObjCount = (int)GameManager::GetGameData().ConfigObjectCount(sceneIndex);

    // Initialize each object by its unique scene&object index combination
    for (int objId = 0; objId < sceneObjCount; objId++)
        CreateObject(sceneIndex, objId);
}

Scene::~Scene() {
    for (SceneObject* ptr : sceneObjects) {
        delete ptr;
    }
}

void Scene::CreateObject(int sceneIndex, int objectIndex) {
    DataLoader& gameData = GameManager::GetGameData();

    // Retrieve non string parameter sources
    string positionString = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_POSITION);
    string activeString = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_ACTIVE);

    // Set or retrieve base object parameters
    Vec2 position = positionString.empty() ? Vec2::Zero() : Vec2(positionString);
    bool active = !(activeString == "false" || activeString == "0");
    string objectType = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_TYPE);
    string tags = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_COMMON_TAGS);

    // Throw if no object type specified
    if(objectType.empty())
        throw logic_error(" Trying to create object with empty object type\n");

    SceneObject* newObject = nullptr;
    if(objectType == OBJECT_MAIN_MENU_MGR){
        newObject = new MainMenuManager(position, active, objectType, tags);
    }
    else if(objectType == OBJECT_HUB_MGR){
        string playerSpawnPos = gameData.ConfigGetParam(sceneIndex, objectIndex, "--player-spawn-pos");
        newObject = new HubManager(position, active, objectType, tags, Vec2(playerSpawnPos));
    }
    else if(objectType == OBJECT_LEVEL_MGR){
        newObject = nullptr;
    }
    else if(objectType == OBJECT_TEXT){
        string contents = gameData.ConfigGetParam(sceneIndex, objectIndex, "--contents");
        newObject = new Text(position, active, objectType, tags, contents);
    }
    else if(objectType == OBJECT_MENU){
        string options = gameData.ConfigGetParam(sceneIndex, objectIndex, "--options");
        newObject = new Menu(position, active, objectType, tags, options);
    }
    else if(objectType == OBJECT_TRIGGER){
        string triggerSize = gameData.ConfigGetParam(sceneIndex, objectIndex, "--trigger-size");
        string targetTag = gameData.ConfigGetParam(sceneIndex, objectIndex, "--target-tag");
        newObject = new Trigger(position, active, objectType, tags, targetTag, Vec2(triggerSize));
    }
    else if(objectType == OBJECT_PLAYER){
        newObject = new Player(position, active, objectType, tags);
    }

    if(!newObject)
        throw logic_error(" Object not created, failed to match type or allocate for type: " + objectType + "\n");

    // Add created object to "active" objects vec
    sceneObjects.push_back(newObject);

    // Call start if scene is already loaded
    if(GameManager::GetGameState() == RUNNING)
        newObject->Start();
}

SceneObject* Scene::GetObjectWithTag(const string &tag) const {
    for (SceneObject* ptr : sceneObjects) {
        if(ptr->HasTag(tag))
            return ptr;
    }
    return nullptr;
}

vector<SceneObject*> Scene::GetObjectsWithTag(const string &tag) const {
    vector<SceneObject*> objects;
    for (SceneObject* ptr : sceneObjects) {
        if(ptr->HasTag(tag))
            objects.push_back(ptr);
    }
    return objects;
}

void Scene::SetActiveObjectsWithTag(bool active, const string &tag) {
    for (SceneObject* ptr : sceneObjects) {
        if(ptr->HasTag(tag))
            ptr->active = active;
    }
}




