#pragma once
#include <string>
#include <sstream>

using std::string;
using std::istringstream;

struct Vec2 {
    Vec2() = default;
    explicit Vec2(int initY = 0, int initX = 0) : y(initY), x(initX) {
    }
    explicit Vec2(const string& yxString) {
        istringstream source(yxString);
        source >> y;
        source >> x;
    }
    Vec2(const Vec2& other) = default;
    ~Vec2() = default;

    Vec2 operator+(const Vec2& other) const {
        return Vec2(y + other.y, x + other.x);
    }
    Vec2 operator*(int scalar) const {
        return Vec2(y * scalar, x * scalar);
    }
    Vec2& operator+=(const Vec2& other) {
        y+=other.y;
        x+=other.x;
        return *this;
    }
    Vec2& operator*=(int scalar) {
        y*=scalar;
        x*=scalar;
        return *this;
    }
    bool operator==(const Vec2& other) const {
        return y==other.y && x==other.x;
    }
    bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }

    static Vec2 Zero() {
        return Vec2(0, 0);
    }

    static Vec2 One() {
        return Vec2(1, 1);
    }

    static Vec2 Up() {
        return Vec2(-1, 0);
    }

    static Vec2 Down() {
        return Vec2(1, 0);
    }

    static Vec2 Left() {
        return Vec2(0, -1);
    }

    static Vec2 Right() {
        return Vec2(0, 1);
    }

    int y = 0, x = 0;
};

