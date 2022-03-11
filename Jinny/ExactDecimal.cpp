#include "ExactDecimal.h"

#include <cmath>

const int Framework::ExactDecimal::DECIMAL_PLACES = 100000;

Framework::ExactDecimal::ExactDecimal(int num)
{
    m_value = (PrecisionValue) num * DECIMAL_PLACES;
}

Framework::ExactDecimal::ExactDecimal(double dec)
{
    dec *= DECIMAL_PLACES;
    m_value = (PrecisionValue)std::round(dec);
}

int Framework::ExactDecimal::getWholeNumber() const
{
    return (int)std::round(m_value / DECIMAL_PLACES);
}

bool Framework::ExactDecimal::isZero() const
{
    return m_value == 0 ? true : false;
}

Framework::ExactDecimal& Framework::ExactDecimal::operator=(int num)
{
    m_value = num * DECIMAL_PLACES;
}

Framework::ExactDecimal& Framework::ExactDecimal::operator=(double decimal)
{
    decimal *= DECIMAL_PLACES;
    m_value = (PrecisionValue) std::round(decimal);
}

Framework::ExactDecimal& Framework::ExactDecimal::operator+=(eDec dec)
{
    m_value += dec.m_value;
    return *this;
}

Framework::ExactDecimal Framework::ExactDecimal::operator+(eDec dec)
{
    ExactDecimal decimal = *this;
    decimal += dec;
    return decimal;
}

Framework::ExactDecimal::operator double()
{
    return m_value / DECIMAL_PLACES;
}
