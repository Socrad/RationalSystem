
#include "rational.h"
#include <stdexcept>
#include <string>

std::pair<long long, long long> Rational::parse(const std::string& num_str) {
    enum class ParsingState {
        CHECK_SIGN,
        CHECK_INTEGER,
        CHECK_FRACTIONAL,
        CHECK_DENOMINATOR
    };

    ParsingState state = ParsingState::CHECK_SIGN;
    int sign = 1, sign_denominator = 1;
    int fractional_length = 0;
    std::string integer_part = "";
    std::string parsed = "";
    long long numerator = 0, denominator = 1;

    try {
        for (char c : num_str) {
            switch (state)
            {
            case ParsingState::CHECK_SIGN:
                if (c == '-') {
                    sign = -1;
                    state = ParsingState::CHECK_INTEGER;
                } else if (c == '+') {
                    state = ParsingState::CHECK_INTEGER;
                } else if (isdigit(c)) {
                    parsed += c;
                    state = ParsingState::CHECK_INTEGER;
                } else if (c == '.') {
                    integer_part = "0";
                    state = ParsingState::CHECK_FRACTIONAL;
                } else throw std::invalid_argument("Invalid start character.");
                break;
            case ParsingState::CHECK_INTEGER:
                if (isdigit(c)) {
                    parsed += c;
                } else if (c == '.') {
                    integer_part = parsed;
                    parsed = "";
                    state = ParsingState::CHECK_FRACTIONAL;
                } else if (c == '/') {
                    numerator = std::stoll(parsed);
                    parsed = "";
                    state = ParsingState::CHECK_DENOMINATOR;
                } else throw std::invalid_argument("Invalid character in integer/numerator part.");
                break;
            case ParsingState::CHECK_FRACTIONAL:
                if (!isdigit(c)) throw std::invalid_argument("Invalid character in fractional part.");
                parsed += c;
                fractional_length++;
                break;
            case ParsingState::CHECK_DENOMINATOR:
                if (parsed.empty() && c == '+' ) break;
                if (parsed.empty() && c == '-' ) {
                    sign_denominator = -1;
                    break;
                }
                if (!isdigit(c)) throw std::invalid_argument("Invalid character in denominator part.");
                parsed += c;
                break;
            }
        }
        switch (state) 
        {
        case ParsingState::CHECK_SIGN:
            throw std::invalid_argument("No number.");
            break;
        case ParsingState::CHECK_INTEGER:
            if (parsed.empty()) {
                throw std::invalid_argument("No number.");
            }
            numerator = std::stoll(parsed);
            denominator = 1;
            break;
        case ParsingState::CHECK_FRACTIONAL:
            numerator = std::stoll(integer_part+parsed);
            denominator = 1;
            for (int i=0;i<fractional_length;i++) {
                denominator *= 10;
            }
            break;
        case ParsingState::CHECK_DENOMINATOR:
            if (parsed.empty()) {
                throw std::invalid_argument("Has no denominator");
            }
            
            denominator = std::stoll(parsed);
            denominator *= sign_denominator;
            break;
        }
        numerator *= sign;
        return {numerator, denominator};
    } catch (const std::out_of_range& e) {
        throw std::invalid_argument("Too large number.");
    } catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Internal parser error or invalid format."+ std::string(e.what()));
    }   
}
