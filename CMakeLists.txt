cmake_minimum_required(VERSION 3.10)

project(explorer)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src/explorer)
add_subdirectory(tests)