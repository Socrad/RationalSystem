# CMake 최소 요구 버전 설정
cmake_minimum_required(VERSION 3.10)
 
# 프로젝트 이름과 언어 설정
project(RationalSystem CXX)

# C++ 표준 설정 (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 실행 파일 생성
# 이름: rational_system_test
# 소스: src/main.cpp
add_executable(
    rational_system_test 
    examples/test_suite.cpp
    src/rational.cpp
    src/rational_parser.cpp
    src/rational_reducer.cpp
    src/rational_converter.cpp
    src/rational_arithmetic.cpp
    src/rational_comparison.cpp
    src/rational_io.cpp
)

# 헤더 파일 경로 추가
target_include_directories(rational_system_test PUBLIC src)
