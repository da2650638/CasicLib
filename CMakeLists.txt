cmake_minimum_required(VERSION 3.15)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

project(CasicCpp LANGUAGES CXX C)

add_subdirectory(CasicLib)
add_subdirectory(Test)

