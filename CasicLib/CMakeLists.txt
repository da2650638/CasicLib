cmake_minimum_required(VERSION 3.15)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

project(CasicLibrary LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(casic SHARED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp src/*.h)

message("CasicLib sources: ${sources}")

target_include_directories(casic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_sources(casic PUBLIC ${sources})

target_compile_definitions(casic PUBLIC 
    PUBLIC
    CASICLIB_EXPORTS    # 定义导出宏
)
