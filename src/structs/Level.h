#pragma once
#include <string>

using std::string;

struct Level{
    Level() = default;
    Level(const Level& other) = default;
    ~Level() = default;
    string title{}; /// Level title
    string description{}; /// Level description
    int sceneIndex = 0; /// Level scene index
    int reward = 0; /// Reward for completing level
};
