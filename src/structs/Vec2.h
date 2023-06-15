#pragma once
#include <string>
#include <sstream>

using std::string;
using std::istringstream;

/**
 * Simplified 2-dimensional vector struct with flipped y,x coords order.
 */
struct Vec2 {
    Vec2() = default;
    /**
     * Create Vec2 with given y,x coordinates
     * @param initY y coordinate
     * @param initX x coordinate
     */
    explicit Vec2(int initY = 0, int initX = 0) : y(initY), x(initX) {
    }
    /**
     * Create Vec2 from string with y,x coordinates from a string.
     * @param yxString string holding y,x coords separated by space
     */
    explicit Vec2(const string& yxString) {
        istringstream source(yxString);
        source >> y;
        source >> x;
    }
    Vec2(const Vec2& other) = default;
    ~Vec2() = default;

    /**
     * Vector addition
     * @param other add vector
     * @return resulting vector
     */
    Vec2 operator+(const Vec2& other) const {
        return Vec2(y + other.y, x + other.x);
    }
    /**
     * Vector multiplication by scalar
     * @param scalar vector scalar
     * @return resulting vector
     */
    Vec2 operator*(int scalar) const {
        return Vec2(y * scalar, x * scalar);
    }
    /**
     * Vector addition
     * @param other add vector
     * @return resulting vector
     */
    Vec2& operator+=(const Vec2& other) {
        y+=other.y;
        x+=other.x;
        return *this;
    }
    /**
    * Vector multiplication by scalar
    * @param scalar vector scalar
    * @return resulting vector
    */
    Vec2& operator*=(int scalar) {
        y*=scalar;
        x*=scalar;
        return *this;
    }
    /**
     * Vector comparison - true if both coordinates equal
     * @param other vector to compare with
     * @return vectors equal
     */
    bool operator==(const Vec2& other) const {
        return y==other.y && x==other.x;
    }
    /**
     * Negated vector comparison - false if both coordinates equal
     * @param other vector to compare with
     * @return vectors not equal
     */
    bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }

    /**
     * Null vector
     * @return vector (0,0)
     */
    static Vec2 Zero() {
        return Vec2(0, 0);
    }
    /**
     * Ones vector
     * @return vector (1,1)
     */
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

    int y = 0, x = 0; /// vector coordinates
};

