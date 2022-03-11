#pragma once

namespace Framework
{

	struct Vector
	{
		double x_value;
		double y_value;


		// Useful operators
		Vector& operator+=(const Vector& vector);
		Vector operator+(const Vector& vector);

		Vector& operator/=(double num);
		Vector operator/(double num);

		Vector& operator*=(double num);
		Vector operator*(double num);


		// Useful Functions
		void clear();
	};
}