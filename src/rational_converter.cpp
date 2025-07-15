#include "rational.h"
#include <string>

std::string Rational::toString() const {
    if (m_denominator == 1) {
        return std::to_string(m_numerator);
    }
    return std::to_string(m_numerator) + "/" + std::to_string(m_denominator);
}

double Rational::toDouble() const {
    return static_cast<double>(m_numerator) / m_denominator;
}
