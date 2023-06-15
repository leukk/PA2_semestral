#pragma once
#include "../singleton-managers/GameManager.h"
#include "../scene-objects-managers/MainMenuManager.h"
#include "../scene-objects-managers/HubManager.h"
#include "../scene-objects-managers/LevelManager.h"
#include "../scene-objects-managers/BulletManager.h"
#include "../scene-objects/Text.h"
#include "../scene-objects/Menu.h"
#include "../scene-objects/Trigger.h"
#include "../scene-objects/Player.h"
#include "../scene-objects/Enemy.h"
#include "../utils/GameConstants.h"
#include "SceneObject.h"
#include <vector>
#include <sstream>

class GameManager;
class SceneObject;

using std::vector;
using std::logic_error;
using std::to_string;

/**
 * Scene - object responsible for holding/updating/creating sceneObjects
 *
 * Can only be constructed by copying / calling explicit constructor which requires
 * sceneId. Scene automatically loads all objects, in case of config failure throws.
 */
class Scene{
public:
    Scene() = delete;
    explicit Scene(int sceneIndex);
    Scene(const Scene& other) = default;
    ~Scene();

    /**
     * Creates sceneObject based on its index within its scene
     *
     * Creates a heap allocated instance of sceneObject matching sceneId
     * and objectId. Type is deduced using its type parameter value.
     * @param sceneIndex objects scene index
     * @param objectIndex objects index within scene
     */
    void CreateObject(int sceneIndex, int objectIndex);
    /**
     * Retrieves first object matching tag, nullptr if none found
     * @param tag tag to match
     * @return scene object pointer / nullptr
     */
    [[nodiscard]] SceneObject* GetObjectWithTag(const string& tag) const;
    /**
     * Retrieves vector of sceneObjects with matching tag, empty vector if none found
     * @param tag tag to match
     * @return vector of sObj pointers
     */
    [[nodiscard]] vector<SceneObject*> GetObjectsWithTag(const string& tag) const;
    /**
     * Sets active property of sceneObjects with matching tag
     * @param active object active state
     * @param tag tag to match
     */
    void SetActiveObjectsWithTag(bool active, const string& tag);

    vector<SceneObject*> sceneObjects; /// Vector of all created sceneObjects
};


