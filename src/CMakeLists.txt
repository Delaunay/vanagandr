project(vanagandr)
cmake_minimum_required(VERSION 2.8.4)
aux_source_directory(. SRC_LIST)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O1 -O2 -O3")

ENABLE_TESTING()

#===============================================================================
#           Libraries
#===============================================================================

# INCLUDE_DIRECTORIES("../../../../libraries/include")
# INCLUDE_DIRECTORIES("/cygdrive/c/Users/pastafarian/Dropbox/libraries/include")

SET(GTEST_DIR "../../gtest/gtest")

#===============================================================================
#           Project Source
#===============================================================================

# Sources
aux_source_directory("${PROJECT_SOURCE_DIR}/file"         SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/finance"      SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/math"         SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/statistic"    SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/test"         SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/future"       SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/future/plot"  SRC_LIST)

# directories
add_subdirectory("${PROJECT_SOURCE_DIR}/file")
add_subdirectory("${PROJECT_SOURCE_DIR}/finance")
add_subdirectory("${PROJECT_SOURCE_DIR}/math")
add_subdirectory("${PROJECT_SOURCE_DIR}/statistic")
add_subdirectory("${PROJECT_SOURCE_DIR}/test")

# future new feature
add_subdirectory("${PROJECT_SOURCE_DIR}/future")
add_subdirectory("${PROJECT_SOURCE_DIR}/future/plot")

#===============================================================================
#           gtest Configuration
#===============================================================================

# Compile the gtest suite
include_directories(${GTEST_DIR})
include_directories("${GTEST_DIR}/include")
add_library(gtest "${GTEST_DIR}/src/gtest-all.cc")

#===============================================================================
#           Compiling
#===============================================================================

add_library(vanagandr ${SRC_LIST})

# link compiled libraries : including gtest
link_directories(${PROJECT_BINARY_DIR})

# executable and linking
add_executable(tests "${PROJECT_SOURCE_DIR}/test/main_test.cpp" ${SRC_LIST})
target_link_libraries(tests -isystem libgtest.a -pthread)
