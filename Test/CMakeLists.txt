cmake_minimum_required(VERSION 3.15)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

project(Test LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Test)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp src/*.h)

message("prject Test sources: ${sources}")

target_link_libraries(Test PRIVATE casic)

target_sources(Test PUBLIC ${sources})

