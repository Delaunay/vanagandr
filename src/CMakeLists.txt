project(vanagandr)
cmake_minimum_required(VERSION 2.8.4)
aux_source_directory(. SRC_LIST)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O1 -O2 -O3")

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
aux_source_directory("${PROJECT_SOURCE_DIR}/AI"           SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/finance"      SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/math"         SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/statistics"   SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/test"         SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/containers"   SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/future"       SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/future/plot"  SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/formating"    SRC_LIST)
aux_source_directory("${PROJECT_SOURCE_DIR}/future/cryptography"  SRC_LIST)

# directories
add_subdirectory("${PROJECT_SOURCE_DIR}/file")
add_subdirectory("${PROJECT_SOURCE_DIR}/finance")
add_subdirectory("${PROJECT_SOURCE_DIR}/math")
add_subdirectory("${PROJECT_SOURCE_DIR}/statistics")
add_subdirectory("${PROJECT_SOURCE_DIR}/containers")
add_subdirectory("${PROJECT_SOURCE_DIR}/test")
add_subdirectory("${PROJECT_SOURCE_DIR}/formating")

# future new feature
add_subdirectory("${PROJECT_SOURCE_DIR}/future")
add_subdirectory("${PROJECT_SOURCE_DIR}/future/plot")
add_subdirectory("${PROJECT_SOURCE_DIR}/future/cryptography")
add_subdirectory("${PROJECT_SOURCE_DIR}/AI")

#include_directories("${PROJECT_SOURCE_DIR}/containers")

# for IDE
SET(HDRS_FILE
        containers/SimpleArray.h
        containers/DataFrame.h
        containers/Queues.h
        containers/Sort.h
        containers/Stack.h
        containers/Type.h
        containers/LinkedList.h
        containers/Capacity.h
        error/Error.h
        error/ErrorConfig.h)


#===============================================================================
#           Ceres-Solver Configuration
#===============================================================================





#===============================================================================
#           Compiling
#===============================================================================

add_library(vanagandr ${SRC_LIST} ${HDRS_FILE})

# link compiled libraries : including gtest
link_directories(${PROJECT_BINARY_DIR})

## executable and linking
#add_executable(tests "${PROJECT_SOURCE_DIR}/test/main_test.cpp" ${SRC_LIST} ${TEST_FILE})
#target_link_libraries(tests -isystem libgtest.a -pthread)

#===============================================================================
#           gtest Configuration
#===============================================================================

ENABLE_TESTING()

# Compile the gtest suite
include_directories(${GTEST_DIR})
include_directories("${GTEST_DIR}/include")
add_library(gtest "${GTEST_DIR}/src/gtest-all.cc")

MACRO (VANAGANDR_TEST NAME)
    ADD_EXECUTABLE(${NAME}_test test/${NAME}_test.cpp)
    TARGET_LINK_LIBRARIES(${NAME}_test vanagandr -isystem gtest.a -pthread)
    ADD_TEST(NAME ${NAME}_test
             COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}_test)
ENDMACRO (VANAGANDR_TEST)

VANAGANDR_TEST(eigen_date)
VANAGANDR_TEST(file)
VANAGANDR_TEST(integration)
VANAGANDR_TEST(linear_reg)
VANAGANDR_TEST(logistic)
VANAGANDR_TEST(matrix)
VANAGANDR_TEST(option)
#VANAGANDR_TEST(pde)
VANAGANDR_TEST(simplearray)
VANAGANDR_TEST(linkedlist)
VANAGANDR_TEST(solver1D)
VANAGANDR_TEST(varmin)
VANAGANDR_TEST(sort)
VANAGANDR_TEST(perceptron)
VANAGANDR_TEST(formating)
