#include "Vector.h"

framework::Vector::Vector(const double x, const double y)
    :x(x), y(y)
{
}

framework::Vector::Vector()
    :Vector(0, 0)
{
}
framework::Vector& framework::Vector::operator+=(const Vector& vector)
{
    x += vector.x;
    y += vector.y;
    return *this;
}

framework::Vector framework::Vector::operator+(const Vector& vector) const
{
    Vector out(*this);
    return out += vector;
}

framework::Vector& framework::Vector::operator-=(const Vector& vector)
{
    x -= vector.x;
    y -= vector.y;
    return *this;
}

framework::Vector framework::Vector::operator-(const Vector& vector) const
{
    Vector out(*this);
    return out -= vector;
}

framework::Vector& framework::Vector::operator/=(const double num)
{
    x /= num;
    y /= num;

    return *this;
}

framework::Vector framework::Vector::operator/(const double num) const
{
    Vector out(*this);
    return out /= num;
}

framework::Vector& framework::Vector::operator*=(const double num)
{
    x *= num;
    y *= num;
    return *this;
}

framework::Vector framework::Vector::operator*(const double num) const
{
    Vector out(*this);
    return out *= num;
}

double& framework::Vector::operator[](const int i)
{
    switch (i)
    {
    case 0:
        return x;
    case 1:
        return y;
    default:
        throw "Vector struct only accepts index 0 or 1";
    }
}

const double& framework::Vector::operator[](const int i) const
{
    switch (i)
    {
    case 0:
        return x;
    case 1:
        return y;
    default:
        throw "Vector struct only accepts index 0 or 1";
    }
}

void framework::Vector::clear()
{
    x = 0;
    y = 0;
}
