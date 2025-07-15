#include <iostream>
#include <stdexcept>
#include <functional> // For std::function
#include <climits>    // For LLONG_MAX
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

void run_simple_tests() {
    std::cout << "--- Running Simple Tests ---" << std::endl;
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational sum = r1 + r2;
    std::cout << r1 << " + " << r2 << " = " << sum << std::endl;

    Rational r3(2);
    Rational r4(1, 4);
    Rational sum2 = r3 + r4;
    std::cout << r3 << " + " << r4 << " = " << sum2 << std::endl;
}

void run_edge_case_tests() {
    std::cout << "\n--- Running Arithmetic Edge Case Tests ---" << std::endl;
    Rational r_half(1, 2);
    Rational r_neg_half(-1, 2);
    Rational r_two(2, 1);
    Rational r_zero(0, 1);
    Rational r_one(1, 1);
    test("Multiply by zero", r_half * r_zero, r_zero);
    test("Multiply by one", r_half * r_one, r_half);
    test_exception("Divide by zero", [&]() { Rational result = r_half / r_zero; });
}

void run_comparison_tests() {
    std::cout << "\n--- Running Comparison Tests ---" << std::endl;
    Rational r_half(1, 2);
    Rational r_another_half(2, 4);
    test_bool("Eq: equivalent", r_half == r_another_half, true);
    test_bool("Neq: equivalent", r_half != r_another_half, false);
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
    run_simple_tests();
    run_edge_case_tests();
    run_comparison_tests();
    run_io_tests();
    // run_interactive_io_test(); // 주석 처리됨. 필요시 주석을 해제하여 직접 테스트 가능

    return 0;
}