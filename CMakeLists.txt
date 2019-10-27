cmake_minimum_required(VERSION 3.14.5)
project(DeskCalculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(DeskCalculator main.cpp catch.hpp parser.h error.h input.h)