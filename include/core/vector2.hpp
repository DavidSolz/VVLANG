#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2
{
private:
    float coords[2];

public:
    Vector2();

    Vector2(const float &x, const float &y);

    Vector2 operator+(const Vector2 &vector) const;

    Vector2 &operator+=(const Vector2 &vector);

    Vector2 operator-(const Vector2 &vector) const;

    Vector2 operator*(const float &scalar) const;

    float *data();

    float &x();

    float &y();
};

#endif