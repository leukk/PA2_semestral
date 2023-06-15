#include "Scene.h"

Scene::Scene(int sceneIndex) {
    // Get number of objects in given sceneIndex
    int sceneObjCount = (int)GameManager::GetGameData().ConfigObjectCount(sceneIndex);

    // Initialize each object by its unique scene&object index combination
    for (int objId = 0; objId < sceneObjCount; objId++)
        CreateObject(sceneIndex, objId);
}

Scene::~Scene() {
    for (SceneObject* object : sceneObjects) {
        delete object;
    }
}

void Scene::CreateObject(int sceneIndex, int objectIndex) {
    DataLoader& gameData = GameManager::GetGameData();

    // Get sceneObject parameters
    string positionString = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_SCENE_OBJECT_POSITION);
    string activeString = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_SCENE_OBJECT_ACTIVE);
    Vec2 position = positionString.empty() ? Vec2::Zero() : Vec2(positionString);
    bool active = !(activeString == "false" || activeString == "0");
    string objectType = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_SCENE_OBJECT_TYPE);
    string tags = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_SCENE_OBJECT_TAGS);

    // Throw if no object type specified
    if(objectType.empty())
        throw logic_error(" Trying to create object with empty object type\n");

    // Get displayObject parameters
    int color = gameData.ConfigGetNumParam(sceneIndex, objectIndex, PARAM_DISPLAY_OBJECT_COLOR);
    string contents = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_DISPLAY_OBJECT_CONTENTS);

    // Get characterObject parameters
    int lives = gameData.ConfigGetNumParam(sceneIndex, objectIndex, PARAM_CHARACTER_LIVES);
    string collisionChars = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_CHARACTER_COLLISION_CHARS);
    string damageChars = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_CHARACTER_DAMAGE_CHARS);
    int moveDelay = gameData.ConfigGetNumParam(sceneIndex, objectIndex, PARAM_CHARACTER_MOVE_DELAY);
    int shootDelay = gameData.ConfigGetNumParam(sceneIndex, objectIndex, PARAM_CHARACTER_SHOOT_DELAY);
    int shootRange = gameData.ConfigGetNumParam(sceneIndex, objectIndex, PARAM_CHARACTER_SHOOT_RANGE);
    int shootVelocity = gameData.ConfigGetNumParam(sceneIndex, objectIndex, PARAM_CHARACTER_SHOOT_VELOCITY);

    SceneObject* newObject = nullptr;
    if(objectType == OBJECT_MAIN_MENU_MGR){
        newObject = new MainMenuManager({position, active, tags});
    }
    else if(objectType == OBJECT_HUB_MGR){
        newObject = new HubManager({position, active, tags});
    }
    else if(objectType == OBJECT_LEVEL_MGR){
        newObject = new LevelManager({position, active, tags});
    }
    else if(objectType == OBJECT_BULLET_MGR){
        newObject = new BulletManager({{position, active, tags}, contents, color}, collisionChars);
    }
    else if(objectType == OBJECT_TEXT){
        newObject = new Text({{position, active, tags}, contents, color});
    }
    else if(objectType == OBJECT_MENU){
        newObject = new Menu({{position, active, tags}, contents, color});
    }
    else if(objectType == OBJECT_TRIGGER){
        string triggerSize = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_TRIGGER_SIZE);
        string targetTag = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_TRIGGER_TARGET);
        newObject = new Trigger({position, active, tags}, Vec2(triggerSize), targetTag);
    }
    else if(objectType == OBJECT_PLAYER){
        newObject = new Player(CharacterObject({{position, active, tags}, contents, color},
                                               lives, collisionChars, damageChars,
                                               moveDelay, shootDelay, shootRange, shootVelocity));
    }
    else if(objectType == OBJECT_ENEMY){
        string moveDirString = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_ENEMY_MOVE_DIR);
        string shootDirString = gameData.ConfigGetParam(sceneIndex, objectIndex, PARAM_ENEMY_SHOOT_DIR);
        newObject = new Enemy(CharacterObject({{position, active, tags}, contents, color},
                                               lives, collisionChars, damageChars,
                                               moveDelay, shootDelay, shootRange, shootVelocity),
                              Vec2(shootDirString), Vec2(moveDirString));
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




