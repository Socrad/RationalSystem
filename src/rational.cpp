#include "rational.h"
#include <stdexcept>
#include <string>

// Initializer
Rational::Rational(long long numerator, long long denominator) : m_numerator(numerator), m_denominator(denominator)
{
    if (m_denominator == 0) {
        throw std::invalid_argument("denominator cannot be 0");
    }
    reduce();
}

Rational::Rational(long long integer) : m_numerator(integer) {}

Rational::Rational(const std::string& num_str) : Rational(parse(num_str)) {}

Rational::Rational(const std::pair<long long, long long>& parsed_pair) : Rational(parsed_pair.first, parsed_pair.second) {}



