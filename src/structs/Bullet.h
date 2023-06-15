#pragma once
#include "Vec2.h"

struct Bullet{
    Bullet() = default;
    Bullet(const Bullet& other) = default;
    ~Bullet() = default;
    Vec2 position = Vec2::Zero(); /// Bullets initial position
    Vec2 direction = Vec2::Zero(); /// Bullets direction
    int moveTimer = 0; /// Bullets move timer variable
    int moveDelay = 0; /// Bullets move delay (time between moving)
    int distanceRemaining = 0; /// Bullets maximum travel distance
    bool active = false; /// Bullet currently active
};


