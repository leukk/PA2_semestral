#pragma once
#include <string>

using std::string;

struct Level{
    Level() = default;
    Level(const Level& other) = default;
    ~Level() = default;
    string title{};
    string description{};
    int sceneIndex = 0;
    int reward = 0;
};
