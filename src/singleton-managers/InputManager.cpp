#include "InputManager.h"

InputManager &InputManager::m_Get() {
    static InputManager inputManager;
    return inputManager;
}

bool InputManager::GetKey(int key) {
    InputManager& inputManager = InputManager::m_Get();
    return inputManager.m_ContainsKey(key);
}

bool InputManager::GetKeyUp(int key) {
    InputManager& inputManager = InputManager::m_Get();
    return inputManager.m_ContainsKey(key, true) && !inputManager.m_ContainsKey(key);
}

bool InputManager::GetKeyDown(int key) {
    InputManager& inputManager = InputManager::m_Get();
    return !inputManager.m_ContainsKey(key, true) && inputManager.m_ContainsKey(key);
}

void InputManager::m_PollInput() {
    // Load all pressed keys to current poll array
    bool keysRemaining = true;
    int keyPress = ERR;
    for (int i = 0; i < KEYS_REGISTER_LIMIT; ++i){
        // Save keys from last poll to last poll array
        m_lastPollKeys[i] = m_currentPollKeys[i];
        // Key inputs still left in current poll -> save to current poll array
        if(keysRemaining && (keyPress = getch()) != ERR){
            m_currentPollKeys[i] = keyPress;
            continue;
        }
        // No more keys - fill rest with ERR
        keysRemaining = false;
        m_currentPollKeys[i] = ERR;
    }
}

bool InputManager::m_ContainsKey(int key, bool lastPoll) {
    // Select array to search
    array<int, KEYS_REGISTER_LIMIT>& keyArray = lastPoll ? m_lastPollKeys : m_currentPollKeys;
    // Go through all registered keys & compare key code
    for (int i = 0; i < KEYS_REGISTER_LIMIT; ++i){
        if (keyArray[i] == key)
            return true;
        if (keyArray[i] == ERR)
            return false;
    }
    return false;
}
