#pragma once

namespace Framework
{
	struct Vector
	{
		Vector(double x, double y);
		double x;
		double y;

		// Useful operators
		Vector& operator+=(const Vector& vector);
		Vector operator+(const Vector& vector);

		Vector& operator-=(const Vector& vector);
		Vector operator-(const Vector& vector);

		Vector& operator/=(double num);
		Vector operator/(double num);

		Vector& operator*=(double num);
		Vector operator*(double num);

		// Vector supports getting and setting by index, where x is 0 and y is 1
		double& operator[](int i);

		// Useful Functions
		void clear();
	};
}