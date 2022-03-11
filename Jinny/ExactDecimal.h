#pragma once

namespace Framework
{
	typedef int PrecisionValue;

	class ExactDecimal
	{
	public:
		explicit ExactDecimal(int num = 0);
		explicit ExactDecimal(double dec);

		int getWholeNumber() const;

		bool isZero() const;
		// Operator
		ExactDecimal& operator=(int num);
		ExactDecimal& operator=(double decimal);

		ExactDecimal& operator+=(ExactDecimal dec);
		ExactDecimal operator+(ExactDecimal dec);

		operator double();

	private:

		PrecisionValue m_value;
		const static int DECIMAL_PLACES;
	};

	typedef ExactDecimal eDec;
}