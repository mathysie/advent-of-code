cmake_minimum_required(VERSION 3.28)

set(VCPKG_INSTALLED_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed")

# set the project name and version
project(AoC2023Day2 VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Day2 Day2.cpp)
target_compile_options(Day2 PRIVATE -Werror -Wall -Wextra)
