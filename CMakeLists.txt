cmake_minimum_required(VERSION 3.10)
project(inplace_heap_sort VERSION 0.0.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
add_compile_options(-Wall -Ofast -gdwarf-3)

file(GLOB_RECURSE sources "src/*.c" "src/**/*.c")
include_directories("include")

add_executable(inplace_heap_sort ${sources})
