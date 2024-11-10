#include "core/vector2.hpp"

Vector2::Vector2()
{
    this->coords[0] = 0.0f;
    this->coords[1] = 0.0f;
}

Vector2::Vector2(const float &x, const float &y)
{
    this->coords[0] = x;
    this->coords[1] = y;
}

Vector2 Vector2::operator+(const Vector2 &vector) const
{
    Vector2 result;

    result.coords[0] = this->coords[0] + vector.coords[0];
    result.coords[1] = this->coords[1] + vector.coords[1];

    return result;
}

Vector2 &Vector2::operator+=(const Vector2 &vector)
{
    this->coords[0] += vector.coords[0];
    this->coords[1] += vector.coords[1];
    return *this;
}

Vector2 Vector2::operator-(const Vector2 &vector) const
{
    Vector2 result;

    result.coords[0] = this->coords[0] - vector.coords[0];
    result.coords[1] = this->coords[1] - vector.coords[1];

    return result;
}

Vector2 Vector2::operator*(const float &scalar) const
{
    Vector2 result;

    result.coords[0] = this->coords[0] * scalar;
    result.coords[1] = this->coords[1] * scalar;

    return result;
}

float *Vector2::data()
{
    return coords;
}

float &Vector2::x()
{
    return coords[0];
}

float &Vector2::y()
{
    return coords[1];
}