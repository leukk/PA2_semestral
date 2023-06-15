#pragma once
#include "../scene-base/DisplayObject.h"
#include <vector>
#include <string>
#include <codecvt>
#include <locale>

using std::vector;
using std::string;
using std::wstring;
using std::wstring_convert;
using std::codecvt_utf8_utf16;

/**
 * Text: inherits DisplayObject
 *
 * Prints UTF8 contents to the gameWindow.
 * @warning Character '!' functions as newline.
 */
class Text : public DisplayObject{
public:
    Text() = delete;
    explicit Text(const DisplayObject& displayObject);
    Text(const Text& other) = default;
    ~Text() override = default;

    /**
     * Start override
     *
     * Converts narrow string contents to
     * wstring using code
     */
    void Start() override;
    /**
     * Render override
     *
     * Renders unicode characters to game screen.
     * @note Does not overwrite characters with empty spaces.
     * @param gameWin game window
     * @param textWin text window
     */
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
private:
    wstring m_wcontent; /// Wide string converted contents
};

