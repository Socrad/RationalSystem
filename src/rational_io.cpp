#include "rational.h"
#include <iostream>
#include <string>
#include <ios>
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.toString();
}
std::istream& operator>>(std::istream& is, Rational& r) {
    std::string input_str;
    is >> input_str;

    try {
        Rational temp(input_str);
        r = temp;
    } catch (const std::invalid_argument& e) {
        is.setstate(std::ios::failbit);
    }

    return is;
}