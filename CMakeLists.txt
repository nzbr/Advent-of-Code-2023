cmake_minimum_required(VERSION 3.26)
project(Advent_of_Code_2023)

set(CMAKE_CXX_STANDARD 23)

add_executable(day1
        day1/day1.cpp
        shared/util.cpp)

add_executable(day2
        day2/day2.cpp
        shared/util.cpp)

add_executable(day3
        day3/day3.cpp
        shared/util.cpp)

add_executable(day4
        day4/day4.cpp
        shared/util.cpp)
