#include "Vector.h"

#include <cmath>
Framework::Vector& Framework::Vector::operator+=(const Vector& vector)
{
    x_value += vector.x_value;
    y_value += vector.y_value;

    /*
    if (abs(x_value) < 0.0000000001)
    {
        x_value = 0;
    }

    if (abs(y_value) < 0.0000000001)
    {
        y_value = 0;
    }
    */
    return *this;
}

Framework::Vector Framework::Vector::operator+(const Vector& vector)
{
    Vector out(*this);
    return out += vector;
}

Framework::Vector& Framework::Vector::operator/=(double num)
{
    x_value /= num;
    y_value /= num;

    /*
    if (abs(x_value) < 0.0000000001)
    {
        x_value = 0;
    }

    if (abs(y_value) < 0.0000000001)
    {
        y_value = 0;
    }
    */

    return *this;
}

Framework::Vector Framework::Vector::operator/(double num)
{
    Vector out(*this);
    return out /= num;
}

Framework::Vector& Framework::Vector::operator*=(double num)
{
    x_value *= num;
    y_value *= num;
    /*
    if (abs(x_value) < 0.00000001)
    {
        x_value = 0;
    }
    
    if (abs(y_value) < 0.00000001)
    {
        y_value = 0;
    }
    */

    return *this;
}

Framework::Vector Framework::Vector::operator*(double num)
{
    Vector out(*this);
    return out *= num;
}

void Framework::Vector::clear()
{
    x_value = 0;
    y_value = 0;
}
