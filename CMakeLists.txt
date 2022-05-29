cmake_minimum_required(VERSION 3.16)

project(Harrow VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

add_compile_definitions(_USE_MATH_DEFINES)

add_executable(harrow src/app.cpp)
