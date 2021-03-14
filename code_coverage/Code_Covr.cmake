cmake_minimum_required(VERSION 3.17)
project(IW_1 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES project/src/utils.c)

add_library(utils STATIC ${SOURCES})
target_include_directories(utils PUBLIC ../project/include)

find_package(GTest REQUIRED)
target_link_libraries(gtests GTest::gtest utils)

########################################################### code_coverage
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/code_coverage/cmake_modules)
if (CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    append_coverage_compiler_flags()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

    set(GCOVR_PATH "/usr/bin/gcovr")

    setup_target_for_coverage_lcov(
            NAME code_covr_lconv
            EXECUTABLE gtests
            DEPENDENCIES gtests utils
    )
    setup_target_for_coverage_gcovr_html(
            NAME code_covr_gcovr_html
            EXECUTABLE gtests
            DEPENDENCIES gtests utils
    )
endif ()
########################################################### code_coverage
