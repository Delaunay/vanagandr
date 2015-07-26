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

SET(TEST_FILE
        test/eigen_date.h
        test/file_test.h
        test/integration_test.h
        test/linear_reg_test.h
        test/linkedlist_test.h
        test/logistic_test.h
        test/matrix_test.h
        test/option_test.h
        test/pde_test.h
        test/simplearray_test.h
        test/solver1D_test.h
        test/varmin_test.h
        test/sort_test.h
        test/perceptron_test.h
        test/formating_test.h)

#===============================================================================
#           gtest Configuration
#===============================================================================

# Compile the gtest suite
include_directories(${GTEST_DIR})
include_directories("${GTEST_DIR}/include")
add_library(gtest "${GTEST_DIR}/src/gtest-all.cc")

#===============================================================================
#           Ceres-Solver Configuration
#===============================================================================


include_directories("${PROJECT_SOURCE_DIR}/containers")


#===============================================================================
#           Compiling
#===============================================================================

add_library(vanagandr ${SRC_LIST} ${HDRS_FILE})

# link compiled libraries : including gtest
link_directories(${PROJECT_BINARY_DIR})

# executable and linking
add_executable(tests "${PROJECT_SOURCE_DIR}/test/main_test.cpp" ${SRC_LIST} ${TEST_FILE})
target_link_libraries(tests -isystem libgtest.a -pthread)
