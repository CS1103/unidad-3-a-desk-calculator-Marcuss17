cmake_minimum_required(VERSION 3.14.5)
project(DeskCalculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(DeskCalculator main.cpp catch.hpp lexer.h error.h parser.h)