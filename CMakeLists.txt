cmake_minimum_required(VERSION 3.17)
project(IW_1 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES project/src/utils.c
            project/src/start_program.c)

add_library(utils STATIC ${SOURCES})
target_include_directories(utils PUBLIC project/include)

add_executable(IW_1 project/src/main.c)
target_link_libraries(IW_1 utils)

find_package(GTest REQUIRED)
add_executable(gtests gtests/gtests.cpp)
target_link_libraries(gtests GTest::gtest utils)