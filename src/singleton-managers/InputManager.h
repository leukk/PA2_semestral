#pragma once
#include <ncurses.h>
#include <array>

#define KEYS_REGISTER_LIMIT 16

using std::array;

/**
 * Input management singleton.
 *
 * @note Cannot be retrieved, has static interface for interaction. (except from main)
 * @bug Due to terminal input behavior all 3 interface methods function
 * the same - return if key is currently being pressed.
 */
class InputManager {
private:
    InputManager() = default;
public:
    InputManager(const InputManager& other) = delete;
    ~InputManager() = default;

    /**
     * Returns true if key currently pressed
     * @param key key code
     * @return key pressed
     */
    static bool GetKey(int key);
    /**
     * Returns true if key currently lifted
     * @param key key code
     * @return key lifted
     * @warning read class bug
     */
    static bool GetKeyUp(int key);
    /**
     * Returns true if key just pressed down
     * @param key key code
     * @return key pressed
     * @warning read class bug
     */
    static bool GetKeyDown(int key);
private:
    friend int main([[maybe_unused]] int argv, char * argc[]);
    /**
     * Singleton reference getter
     * @return global instance
     */
    static InputManager& m_Get();
    /**
     * Poll keys pressed this poll
     *
     * Polls all user input during single poll.
     * Max KEYS_REGISTER_LIMIT can be registered at a time.
     */
    void m_PollInput();
    /**
     * Key with given keycode registered in keypress array;
     *
     * @param key keycode
     * @param lastPoll check last key poll instead
     * @return key pressed
     */
    bool m_ContainsKey(int key, bool lastPoll = false);

    array<int, KEYS_REGISTER_LIMIT> m_lastPollKeys; /// Pressed keys during last poll
    array<int, KEYS_REGISTER_LIMIT> m_currentPollKeys; /// Pressed keys during current poll
};

