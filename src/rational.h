#pragma once

#include <string>

class Rational {
public:
    Rational() = default;
    Rational(long long numerator, long long denominator);
    Rational(long long integer);
    Rational(const std::string& num_str);
    Rational(const std::pair<long long, long long>& parsed_pair);

    std::string toString() const;
    double toDouble() const;

    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;

    Rational operator-() const;

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator<(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>=(const Rational& other) const;

private:
    long long m_numerator = 0;
    long long m_denominator = 1;

    static std::pair<long long, long long> parse(const std::string& num_str);

    void reduce();
};

std::ostream& operator<<(std::ostream& os, const Rational& r);
std::istream& operator>>(std::istream& os, Rational& r);