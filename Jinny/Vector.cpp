#include "Vector.h"

#include <cmath>
Framework::Vector::Vector(double x, double y)
    :x(x), y(y)
{
}

Framework::Vector::Vector()
    :Vector(0, 0)
{
}
Framework::Vector& Framework::Vector::operator+=(const Vector& vector)
{
    x += vector.x;
    y += vector.y;
    return *this;
}

Framework::Vector Framework::Vector::operator+(const Vector& vector)
{
    Vector out(*this);
    return out += vector;
}

Framework::Vector& Framework::Vector::operator-=(const Vector& vector)
{
    x -= vector.x;
    y -= vector.y;
    return *this;
}

Framework::Vector Framework::Vector::operator-(const Vector& vector)
{
    Vector out(*this);
    return out -= vector;
}

Framework::Vector& Framework::Vector::operator/=(double num)
{
    x /= num;
    y /= num;

    return *this;
}

Framework::Vector Framework::Vector::operator/(double num)
{
    Vector out(*this);
    return out /= num;
}

Framework::Vector& Framework::Vector::operator*=(double num)
{
    x *= num;
    y *= num;
    return *this;
}

Framework::Vector Framework::Vector::operator*(double num)
{
    Vector out(*this);
    return out *= num;
}

double& Framework::Vector::operator[](int i)
{
    switch (i)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    default:
        throw "Vector struct only accepts index 0 or 1";
        break;
    }
}

double Framework::Vector::operator[](int i) const
{
    switch (i)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    default:
        throw "Vector struct only accepts index 0 or 1";
        break;
    }
}

void Framework::Vector::clear()
{
    x = 0;
    y = 0;
}
