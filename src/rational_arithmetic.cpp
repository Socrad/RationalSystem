#include "rational.h"
#include <numeric>
#include <stdexcept>
#include <climits>
#include <utility>

Rational Rational::operator+(const Rational& other) const {
    __int128_t lcm = static_cast<__int128_t>(m_denominator) / std::gcd(m_denominator, other.m_denominator) * other.m_denominator;

    __int128_t new_numerator = (static_cast<__int128_t>(m_numerator) * (lcm/m_denominator)) + (static_cast<__int128_t>(other.m_numerator) * (lcm/other.m_denominator));

    if (new_numerator > LLONG_MAX || new_numerator < LLONG_MIN) {
        throw std::overflow_error("Result numerator out of long long range.");
    } 

    if (lcm > LLONG_MAX || lcm < LLONG_MIN) {
        throw std::overflow_error("Result denominator out of long long range.");
    }
    return Rational(static_cast<long long>(new_numerator), static_cast<long long>(lcm));
}

Rational Rational::operator-() const {
    if (m_numerator == LLONG_MIN) {
        throw std::overflow_error("Result numerator out of long long range.");
    }
    return Rational(-m_numerator, m_denominator);
}

Rational Rational::operator-(const Rational& other) const {
    return *this + (-other);
}

Rational Rational::operator*(const Rational& other) const {
    __int128_t mult_numerator = static_cast<__int128_t>(m_numerator) * other.m_numerator;
    __int128_t mult_denominator = static_cast<__int128_t>(m_denominator) * other.m_denominator;
   
    __int128_t a = mult_numerator;
    __int128_t b = mult_denominator;

    while(b) {
        a %= b;
        std::swap(a, b);
    } // 유클리드 호제법, a 의 최종값이 gcd

    mult_numerator /= a;
    mult_denominator /= a;

    if (mult_numerator > LLONG_MAX || mult_numerator < LLONG_MIN) {
        throw std::overflow_error("Result numerator out of long long range.");
    }

    if (mult_denominator > LLONG_MAX ) {
        throw std::overflow_error("Result denominator out of long long range.");
    }

    return Rational(static_cast<long long>(mult_numerator), static_cast<long long>(mult_denominator));   
}

Rational Rational::operator/(const Rational& other) const {
    return *this * Rational(other.m_denominator, other.m_numerator);
}

Rational& Rational::operator+=(const Rational& other) {
    __int128_t lcm = static_cast<__int128_t>(m_denominator) / std::gcd(m_denominator, other.m_denominator) * other.m_denominator;

    __int128_t new_numerator = (static_cast<__int128_t>(m_numerator) * (lcm/m_denominator)) + (static_cast<__int128_t>(other.m_numerator) * (lcm/other.m_denominator));

    if (new_numerator > LLONG_MAX || new_numerator < LLONG_MIN) {
        throw std::overflow_error("Result numerator out of long long range.");
    } 

    if (lcm > LLONG_MAX || lcm < LLONG_MIN) {
        throw std::overflow_error("Result denominator out of long long range.");
    }
    m_denominator = static_cast<long long>(lcm);
    m_numerator = static_cast<long long>(new_numerator);

    reduce();
    
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    *this += (-other);
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
     __int128_t mult_numerator = static_cast<__int128_t>(m_numerator) * other.m_numerator;
    __int128_t mult_denominator = static_cast<__int128_t>(m_denominator) * other.m_denominator;
   
    __int128_t a = mult_numerator;
    __int128_t b = mult_denominator;

    while(b) {
        a %= b;
        std::swap(a, b);
    } // 유클리드 호제법, a 의 최종값이 gcd

    mult_numerator /= a;
    mult_denominator /= a;

    if (mult_numerator > LLONG_MAX || mult_numerator < LLONG_MIN) {
        throw std::overflow_error("Result numerator out of long long range.");
    }

    if (mult_denominator > LLONG_MAX ) {
        throw std::overflow_error("Result denominator out of long long range.");
    }

    m_denominator = static_cast<long long>(mult_denominator);
    m_numerator = static_cast<long long>(mult_numerator);

    // 0인 경우 분모를 1로 정규화
    if (m_numerator == 0) {
        m_denominator = 1;
    }
    // a가 음수가 되어 뒤집힌 부호를 바로잡아야 한다.
    if (m_denominator < 0) {
        m_numerator = -m_numerator;
        m_denominator = -m_denominator;
    }
    
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    *this *= Rational(other.m_denominator, other.m_numerator);
    return *this;
}