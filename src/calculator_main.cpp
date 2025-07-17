#include "rational.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <operand1> <operator> <operand2>" << std::endl;
    std::cerr << "Example: " << argv[0] << " \"1/2\" \"+\" \"1/3\"" << std::endl;
    return 1; // Indicate error
  }

  std::string operand1_str = argv[1];
  std::string op_str = argv[2];
  std::string operand2_str = argv[3];

  try {
    Rational r1(operand1_str);
    Rational r2(operand2_str);

    if (op_str == "+") {
      std::cout << (r1 + r2) << std::endl;
      return 0;
    } else if (op_str == "-") {
      std::cout << (r1 - r2) << std::endl;
      return 0;
    } else if (op_str == "*") {
      std::cout << (r1 * r2) << std::endl;
      return 0;
    } else if (op_str == "/") {
      std::cout << (r1 / r2) << std::endl;
      return 0;
    } else if (op_str == "==") {
      std::cout << std::boolalpha << (r1 == r2) << std::endl;
      return 0;
    } else if (op_str == "!=") {
      std::cout << std::boolalpha << (r1 != r2) << std::endl;
      return 0;
    } else if (op_str == "<") {
      std::cout << std::boolalpha << (r1 < r2) << std::endl;
      return 0;
    } else if (op_str == "<=") {
      std::cout << std::boolalpha << (r1 <= r2) << std::endl;
      return 0;
    } else if (op_str == ">=") {
      std::cout << std::boolalpha << (r1 >= r2) << std::endl;
      return 0;
    } else if (op_str == ">") {
      std::cout << std::boolalpha << (r1 > r2) << std::endl;
      return 0;
    } else {
      std::cerr << "Error: Invalid operator '" << op_str << "'" << std::endl;
      return 1;
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "Error parsing input: " << e.what() << std::endl;
    return 1;
  } catch (const std::overflow_error& e) {
    std::cerr << "Error during calcuration (overflow): " << e.what() << std::endl;
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    return 1;
  }
}