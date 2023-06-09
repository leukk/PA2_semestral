#pragma once
#include "GameManager.h"
#include <ncurses.h>
#include <array>

#define KEYS_REGISTER_LIMIT 16

using std::array;

class InputManager {
private:
    InputManager() = default;
public:
    InputManager(const InputManager& other) = delete;
    ~InputManager() = default;

    static bool GetKey(int key);
    static bool GetKeyUp(int key);
    static bool GetKeyDown(int key);
private:
    friend int main([[maybe_unused]] int argv, char * argc[]);
    static InputManager& m_Get();
    void m_PollInput();
    bool m_ContainsKey(int key, bool lastPoll = false);

    array<int, KEYS_REGISTER_LIMIT> m_lastPollKeys;
    array<int, KEYS_REGISTER_LIMIT> m_currentPollKeys;
};

