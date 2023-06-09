class Vec2 {
public:
    Vec2() = default;
    explicit Vec2(int initY = 0, int initX = 0);
    Vec2(const Vec2& other) = default;
    Vec2& operator=(const Vec2& other) = default;
    ~Vec2() = default;

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator*(int scalar) const;
    Vec2& operator+=(const Vec2& other);
    Vec2& operator*=(int scalar);
    bool operator==(const Vec2& other) const;
    bool operator!=(const Vec2& other) const;

    static Vec2 Zero();

    int y = 0, x = 0;
};

