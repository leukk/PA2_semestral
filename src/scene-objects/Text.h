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

class Text : public DisplayObject{
public:
    Text() = delete;
    explicit Text(const DisplayObject& displayObject);
    Text(const Text& other) = default;
    ~Text() override = default;

    void Start() override;
    bool Update(int updateDeltaMs) override;
    void Render(WINDOW *gameWin, WINDOW *textWin) override;
    void SetContents(const string& contents);

private:
    wstring m_wcontent;
};

