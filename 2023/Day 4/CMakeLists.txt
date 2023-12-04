cmake_minimum_required(VERSION 3.28)

set(VCPKG_INSTALLED_DIR "${CMAKE_SOURCE_DIR}/vcpkg_installed")

# set the project name and version
project(AoC2023Day4 VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Day4 Day4.cpp)

find_package(range-v3 CONFIG REQUIRED)
target_link_libraries(Day4 PRIVATE range-v3::range-v3)
target_compile_options(Day4 PRIVATE -Werror -Wall -Wextra)