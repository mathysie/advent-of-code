cmake_minimum_required(VERSION 3.28)

# set the project name and version
project(AoC2023Day1 VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Day1 Day1.cpp)
target_compile_options(Day1 PRIVATE -Werror -Wall -Wextra)


