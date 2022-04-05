#pragma once

namespace framework
{
    /**
     * \brief A container for two doubles
     */
    struct Vector
    {
        Vector(double x, double y);
        Vector();
        double x;
        double y;

        // Useful operators
        Vector& operator+=(const Vector& vector);
        Vector operator+(const Vector& vector) const;

        Vector& operator-=(const Vector& vector);
        Vector operator-(const Vector& vector) const;

        Vector& operator/=(double num);
        Vector operator/(double num) const;

        Vector& operator*=(double num);
        Vector operator*(double num) const;

        // Vector supports getting and setting by index, where x is 0 and y is 1
        double& operator[](int i);
        const double& operator[](int i) const;

        // Useful Functions
        void clear();
    };
}