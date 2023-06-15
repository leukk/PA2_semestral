#pragma once
#include "Vec2.h"

struct Bullet{
    Bullet() = default;
    Bullet(const Bullet& other) = default;
    ~Bullet() = default;
    Vec2 position = Vec2::Zero();
    Vec2 direction = Vec2::Zero();
    int moveTimer = 0;
    int moveDelay = 0;
    int distanceRemaining = 0;
    bool active = false;
};


