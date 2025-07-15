# RationalSystem

C++17 class for handling rational numbers.

## About The Project

This project provides a comprehensive `Rational` class in C++ that represents numbers as a ratio of two integers (a numerator and a denominator). It is designed to be a drop-in replacement for floating-point types in scenarios where precision is critical.

## Features

*   **Safe Arithmetic Operations:** All standard arithmetic operators (`+`, `-`, `*`, `/`) are implemented using `__int128_t` for intermediate calculations to prevent overflow.
*   **Optimized Compound Assignments:** `+=`, `-=`, `*=`, `/=` are optimized to modify objects in-place, avoiding temporary object creation.
*   **Full Set of Comparison Operators:** `==`, `!=`, `<`, `>`, `<=`, `>=` are implemented efficiently.
*   **Multiple Constructors:** Create `Rational` objects from:
    *   Numerator and denominator.
    *   A single integer.
    *   A string (e.g., `"1/2"`, `"-5"`, `"2.5"`, `"10/-3"`).
*   **Automatic Reduction:** All rational numbers are automatically reduced to their simplest form with a positive denominator (e.g., `4/8` becomes `1/2`, `1/-2` becomes `-1/2`).
*   **Exception Safety:** Throws `std::invalid_argument` for parsing errors or division by zero, and `std::overflow_error` for results that exceed `long long` limits.
*   **Stream I/O:** Seamlessly works with `std::cout` and `std::cin` via `<<` and `>>` operator overloads.
*   **CMake Build System:** Includes a `CMakeLists.txt` for building the example test suite.

## How to Use (Integration)

This project is a library, not a standalone application. To use the `Rational` class in your own project, follow these steps:

1.  **Copy the source files:**
    Copy all `.h` and `.cpp` files from the `src/` directory into your project's source tree.

2.  **Add to your build system:**
    Add the copied `.cpp` files (`rational.cpp`, `rational_arithmetic.cpp`, etc.) to your build process (e.g., in your `CMakeLists.txt` or Makefile).

3.  **Include the header:**
    In your code, simply include the main header file:
    ```cpp
    #include "rational.h"
    ```

## Building the Example

The `examples/test_suite.cpp` file is not part of the library but serves as a comprehensive example and test suite. You can build and run it to see the library in action and verify its functionality.

### Prerequisites

*   A C++17 compatible compiler (e.g., GCC, Clang, MSVC)
*   CMake (version 3.10 or higher, for building the Example.)

### Build and Run Commands
```sh
# Create a build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the example application
./rational_system_test
```

## Usage Example

Here is a minimal example of how to use the `Rational` class:

```cpp
#include <iostream>
#include "rational.h"

int main() {
    // Create from numerator/denominator
    Rational r1(1, 2);

    // Create from a string
    Rational r2("0.75");

    std::cout << "r1 = " << r1 << std::endl; // Outputs: r1 = 1/2
    std::cout << "r2 = " << r2 << std::endl; // Outputs: r2 = 3/4

    // Perform arithmetic
    Rational sum = r1 + r2;
    std::cout << "Sum = " << sum << std::endl; // Outputs: Sum = 5/4

    // Perform comparison
    if (r1 < r2) {
        std::cout << "r1 is less than r2" << std::endl;
    }
    return 0;
}
```

## Acknowledgements

This project was developed in collaboration with Google's Gemini. Gemini served as a project manager and tutor, providing guidance on C++ best practices, code reviews, and debugging assistance throughout the development process.


## License

Distributed under the MIT License. See LICENSE for more information.
```










