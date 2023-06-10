#include "Vec2.h"

Vec2::Vec2(int initY, int initX) : y(initY), x(initX) {
}

Vec2::Vec2(const string& yxString) {
    istringstream source(yxString);
    source >> y;
    source >> x;
}

Vec2 Vec2::operator+(const Vec2 &other) const {
    return Vec2(y + other.y, x + other.x);
}

Vec2 Vec2::operator*(int scalar) const {
    return Vec2(y * scalar, x * scalar);
}

Vec2 &Vec2::operator+=(const Vec2 &other) {
    y+=other.y;
    x+=other.x;
    return *this;
}

Vec2 &Vec2::operator*=(int scalar) {
    y*=scalar;
    x*=scalar;
    return *this;
}

bool Vec2::operator==(const Vec2& other) const {
    return y==other.y && x==other.x;
}

bool Vec2::operator!=(const Vec2& other) const {
    return !(*this == other);
}

Vec2 Vec2::Zero() {
    return Vec2(0, 0);
}

