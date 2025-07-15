#include <iostream>
#include <stdexcept>
#include <functional> // For std::function
#include <climits>    // For LLONG_MIN, LLONG_MAX
#include <sstream>    // For std::stringstream
#include <limits>     // For std::numeric_limits
#include "rational.h"

// Helper function to print test results for Rational objects
void test(const std::string& test_name, const Rational& result, const Rational& expected) {
    std::cout << "[" << test_name << "] ";
    if (result.toString() == expected.toString()) {
        std::cout << "PASS: " << result.toString() << std::endl;
    } else {
        std::cout << "FAIL: Got " << result.toString() << ", Expected " << expected.toString() << std::endl;
    }
}

// Helper function to print test results for boolean values
void test_bool(const std::string& test_name, bool result, bool expected) {
    std::cout << "[" << test_name << "] ";
    if (result == expected) {
        std::cout << "PASS: Result is " << std::boolalpha << result << std::endl;
    } else {
        std::cout << "FAIL: Got " << std::boolalpha << result << ", Expected " << expected << std::endl;
    }
}

void test_exception(const std::string& test_name, std::function<void()> test_func) {
    std::cout << "[" << test_name << "] ";
    try {
        test_func();
        std::cout << "FAIL: Expected exception, but none was thrown." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "PASS: Caught expected exception: " << e.what() << std::endl;
    }
}

void run_arithmetic_tests() {
    std::cout << "\n--- Running Comprehensive Arithmetic Tests ---" << std::endl;
    // Positive numbers
    test("Add: 1/2 + 1/3", Rational(1, 2) + Rational(1, 3), Rational(5, 6));
    test("Subtract: 1/2 - 1/3", Rational(1, 2) - Rational(1, 3), Rational(1, 6));
    test("Multiply: 2/3 * 3/4", Rational(2, 3) * Rational(3, 4), Rational(1, 2));
    test("Divide: 1/2 / 3/4", Rational(1, 2) / Rational(3, 4), Rational(2, 3));

    // Involving negative numbers
    test("Add: 1/2 + (-1/3)", Rational(1, 2) + Rational(-1, 3), Rational(1, 6));
    test("Subtract: -1/2 - 1/3", Rational(-1, 2) - Rational(1, 3), Rational(-5, 6));
    test("Multiply: -1/2 * 1/3", Rational(-1, 2) * Rational(1, 3), Rational(-1, 6));
    test("Divide: -1/2 / -1/3", Rational(-1, 2) / Rational(-1, 3), Rational(3, 2));

    // Resulting in zero or integers
    test("Add to zero", Rational(1, 2) + Rational(-1, 2), Rational(0, 1));
    test("Subtract to zero", Rational(1, 3) - Rational(1, 3), Rational(0, 1));
    test("Multiply to integer", Rational(3, 2) * Rational(2, 1), Rational(3, 1));
    test("Divide to integer", Rational(1, 2) / Rational(1, 4), Rational(2, 1));
}

void run_parser_tests() {
    std::cout << "\n--- Running Parser Tests ---" << std::endl;
    test("Parser: with spaces", Rational(" 1 / 2 "), Rational(1, 2));
    test("Parser: negative with spaces", Rational(" - 3 / 4 "), Rational(-3, 4));
    test("Parser: integer with spaces", Rational("  -5  "), Rational(-5));
    test_exception("Parser: invalid string", [](){ Rational r("abc"); });
    test_exception("Parser: invalid format", [](){ Rational r("1 / / 2"); });
    test_exception("Parser: denominator is zero", [](){ Rational r("1/0"); });
    // Note: LLONG_MAX is 9223372036854775807
    test_exception("Parser: out of range", [](){ Rational r("9223372036854775808"); });
}

void run_edge_case_tests() {
    std::cout << "\n--- Running Arithmetic Edge Case Tests ---" << std::endl;
    Rational r_zero(0, 1);
    Rational r_one(1, 1);
    test("Multiply by zero", Rational(1, 2) * r_zero, r_zero);
    test("Multiply by one", Rational(1, 2) * r_one, Rational(1, 2));
    test_exception("Divide by zero", [&]() { Rational result = Rational(1, 2) / r_zero; });

    // Reduction tests
    test("Reduction: negative denominator", Rational(2, -4), Rational(-1, 2));
    test("Reduction: zero numerator", Rational(0, 5), Rational(0, 1));
    
    std::cout << "\n--- Running Overflow and Limit Tests ---" << std::endl;
    // Unary minus
    Rational r_llong_min(LLONG_MIN, 1);
    test_exception("Negation of LLONG_MIN", [&](){ -r_llong_min; });

    // Addition
    Rational r_llong_max(LLONG_MAX, 1);
    test_exception("Addition overflow", [&](){ r_llong_max + r_one; });

    // Subtraction
    test_exception("Subtraction overflow", [&](){ r_llong_min - r_one; });

    // Multiplication
    test_exception("Multiplication overflow", [&](){ Rational(LLONG_MAX, 1) * Rational(2, 1); });
}

void run_comparison_tests() {
    std::cout << "\n--- Running Comprehensive Comparison Tests ---" << std::endl;
    // Equality
    test_bool("Eq: 1/2 == 2/4", Rational(1, 2) == Rational(2, 4), true);
    test_bool("Neq: 1/2 != 1/3", Rational(1, 2) != Rational(1, 3), true);

    // Less than / Greater than
    test_bool("LT: 1/5 < 2/5", Rational(1, 5) < Rational(2, 5), true);
    test_bool("GT: 1/4 > 1/5", Rational(1, 4) > Rational(1, 5), true);
    test_bool("LT: 2/3 < 3/4", Rational(2, 3) < Rational(3, 4), true);
    test_bool("LT: -1/2 < 1/100", Rational(-1, 2) < Rational(1, 100), true);
    test_bool("LT: -1/2 < -1/3", Rational(-1, 2) < Rational(-1, 3), true);
    test_bool("GT: -1/3 > -1/2", Rational(-1, 3) > Rational(-1, 2), true);
    
    // Less than or equal to / Greater than or equal to
    test_bool("LE: 1/2 <= 1/2", Rational(1, 2) <= Rational(1, 2), true);
    test_bool("GE: 1/2 >= 1/2", Rational(1, 2) >= Rational(1, 2), true);
    test_bool("LE: 1/3 <= 1/2", Rational(1, 3) <= Rational(1, 2), true);
    test_bool("GE: 1/2 >= 1/3", Rational(1, 2) >= Rational(1, 3), true);

    // Comparison with zero
    test_bool("LT: -1/10 < 0", Rational(-1, 10) < Rational(0), true);
    test_bool("GT: 1/10 > 0", Rational(1, 10) > Rational(0), true);
    test_bool("EQ: 0 == 0", Rational(0) == Rational(0, 10), true);

    // Comparison with integers
    test_bool("LT: 5/2 < 3", Rational(5, 2) < Rational(3), true);
    test_bool("GT: 5/2 > 2", Rational(5, 2) > Rational(2), true);
}

void run_io_tests() {
    std::cout << "\n--- Running I/O Stream Tests ---" << std::endl;

    // Test operator<<
    std::stringstream ss_out;
    ss_out << Rational(-7, 3);
    test_bool("Output Stream Test", ss_out.str() == "-7/3", true);

    // Test operator>> - Success cases
    Rational r1, r2, r3;
    std::stringstream ss_in_success("1/2 -5 10/-3");
    ss_in_success >> r1 >> r2 >> r3;
    test("Input Stream: 1/2", r1, Rational(1, 2));
    test("Input Stream: -5", r2, Rational(-5));
    test("Input Stream: 10/-3", r3, Rational(-10, 3));

    // Test operator>> - Failure case
    Rational r_fail;
    std::stringstream ss_in_fail("hello");
    ss_in_fail >> r_fail;
    test_bool("Input Stream: Failbit check", ss_in_fail.fail(), true);
}

void run_interactive_io_test() {
    std::cout << "\n--- Interactive I/O Test ---" << std::endl;
    Rational r;
    std::cout << "Enter a rational number (e.g., 3/4, -5, 2.5): ";
    
    while (!(std::cin >> r)) {
        std::cout << "Invalid input. Please try again: ";
        // Clear error flags
        std::cin.clear();
        // Discard bad input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "You entered: " << r << std::endl;
}

int main() {
    run_arithmetic_tests();
    run_parser_tests();
    run_edge_case_tests();
    run_comparison_tests();
    run_io_tests();
    // run_interactive_io_test(); // 주석 처리됨. 필요시 주석을 해제하여 직접 테스트 가능

    return 0;
}