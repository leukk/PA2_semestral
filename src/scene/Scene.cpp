#include "Scene.h"

 Scene::Scene(int sceneId) {
    // Get game data & number of objects in given scene
    DataLoader& gameData = GameManager::Get().gameData;
    int sceneObjCount = (int)gameData.ConfigObjectCount(sceneId);

    // Initialize each object by its prefix
    for (int objId = 0; objId < sceneObjCount; objId++)
        CreateObject(sceneId, objId);

    for (auto obj : sceneObjects)
        obj->Start();
}

Scene::~Scene() {
    for (SceneObject* ptr : sceneObjects) {
        delete ptr;
    }
}

void Scene::CreateObject(int sceneIndex, int objectIndex) {
    DataLoader& gameData = GameManager::Get().gameData;

    // Get object type
    string typeParam = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_OBJECT_TYPE);
    if(typeParam.empty())
        throw logic_error("Invalid object type: " + typeParam);

    // Retrieve common parameters
    string tags = gameData.ConfigGetParam(sceneIndex, objectIndex, "--tags");
    string position = gameData.ConfigGetParam(sceneIndex, objectIndex, "--position");
    string size = gameData.ConfigGetParam(sceneIndex, objectIndex, "--size");

    SceneObject* newObject = nullptr;
    if(typeParam == OBJECT_MAIN_MENU){
        string title = gameData.ConfigGetParam(sceneIndex, objectIndex, "--title");
        string description = gameData.ConfigGetParam(sceneIndex, objectIndex, "--description");
        newObject = new MainMenu(OBJECT_MAIN_MENU, tags, title, description);
    }
    if(typeParam == OBJECT_TEXT){
        string contents = gameData.ConfigGetParam(sceneIndex, objectIndex, "--contents");
        newObject = new Text(OBJECT_MAIN_MENU, tags, contents, Vec2(position));
    }

    if(!newObject)
        throw logic_error("Object not created, failed to match type or allocate for type: " + typeParam + "\n");

    // Add created object to "active" objects vec
    sceneObjects.push_back(newObject);

    // m_Initialize object & call start if scene is already loaded
    newObject->Initialize();
    if(GameManager::Get().GetGameState() == RUNNING)
        newObject->Start();
}




