#include "rational.h"
#include <numeric>

void Rational::reduce() {
    if (m_numerator == 0) {
        m_denominator = 1;
        return;
    }

    long long gcd = std::gcd(m_numerator, m_denominator);
    m_numerator /= gcd;
    m_denominator /= gcd;

    if (m_denominator < 0) {
        m_numerator = -m_numerator;
        m_denominator = -m_denominator;
    }
}
