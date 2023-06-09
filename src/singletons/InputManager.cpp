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
    bool keysRemaining = true;
    int keyPress = ERR;
    for (int i = 0; i < KEYS_REGISTER_LIMIT; ++i){
        m_lastPollKeys[i] = m_currentPollKeys[i];
        if(keysRemaining && (keyPress = getch()) != ERR){
            m_currentPollKeys[i] = keyPress;
            continue;
        }
        keysRemaining = false;
        m_currentPollKeys[i] = ERR;
    }
}

bool InputManager::m_ContainsKey(int key, bool lastPoll) {
    array<int, KEYS_REGISTER_LIMIT>& keyArray = lastPoll ? m_lastPollKeys : m_currentPollKeys;
    for (int i = 0; i < KEYS_REGISTER_LIMIT; ++i){
        if (keyArray[i] == key)
            return true;
        if (keyArray[i] == ERR)
            return false;
    }
    return false;
}
