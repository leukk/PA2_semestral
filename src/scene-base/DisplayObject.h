#pragma once
#include "SceneObject.h"
#include <string>

using std::string;
using std::wstring;

/**
 * DisplayObject derived base class.
 *
 * Adds content / color data & basic Render implementation for objects that display to screen.
 * @note Standalone serves little to no purpose.
 */
class DisplayObject : public SceneObject {
public:
    DisplayObject() = delete;
    DisplayObject(const SceneObject& sceneObject, string content, int color);
    DisplayObject(const DisplayObject& other) = default;
    ~DisplayObject() override = default;

    void Start() override;
    bool Update(int deltaMs) override;
    /**
     * Render override
     *
     * Renders m_content to game window using m_color
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW * gameWin, WINDOW * textWin) override;

protected:
    string m_content;
    int m_color;
};

