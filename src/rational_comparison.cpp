#include "rational.h"

bool Rational::operator==(const Rational& other) const {
    return (m_numerator == other.m_numerator) && (m_denominator == other.m_denominator);
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

bool Rational::operator<(const Rational& other) const {
   // a/b < c/d    a*d < b*c
   __int128_t left = static_cast<__int128_t>(m_numerator) * other.m_denominator;
   __int128_t right = static_cast<__int128_t>(other.m_numerator) * m_denominator;
   return left < right;
}

bool Rational::operator>(const Rational& other) const {
    return other < *this;
}

bool Rational::operator<=(const Rational& other) const {
    return !(other < *this);
}

bool Rational::operator>=(const Rational& other) const {
    return !(*this < other);
}