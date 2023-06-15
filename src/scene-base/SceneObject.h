#pragma once
#include "../structs/Vec2.h"
#include <ncurses.h>
#include <string>

using std::string;

/**
 * Base class of all scene objects.
 *
 * Contains basic information such as position, active state and tags.
 * Class is not pure virtual to enable constructing derived objects with its instance.
 * @note Standalone serves little to no purpose.
 */
class SceneObject {
public:
    SceneObject() = delete;
    SceneObject(Vec2 pos, bool active, string tags);
    SceneObject(const SceneObject& other) = default;
    virtual ~SceneObject() = default;

    /**
     * Virtual Start method.
     * Method is called as soon as scene update cycle starts.
     * All config defined objects are able to be fetched
     */
    virtual void Start();
    /**
     * Virtual Update method.
     * Method is repeatedly called in time intervals defined by global update-rate parameter.
     */
    virtual bool Update(int updateDeltaMs);
    virtual void Render(WINDOW * gameWin, WINDOW * textWin);

    /**
     * Checks if object has tag
     * @param tag tag to check against
     * @return object contains tag
     */
    bool HasTag(const string& tag);

    /**
     * Checks character at position in a certain window belongs within a group of chars
     * @param window window to check in
     * @param pos position to check at
     * @param charGroup characterGroup to find
     * @return one of characterGroup chars at position
     */
    static bool CheckWindowPosForChar(WINDOW *window, Vec2 pos, const string &charGroup);

public:
    Vec2 position; /// Object position on screen
    bool active; /// Object is active (being updated & rendered)
protected:
    string m_tags; /// Object tags
};



