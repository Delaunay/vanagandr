project(vanagandr)
cmake_minimum_required(VERSION 2.8.4)


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
aux_source_directory(file         SRC_LIST)
aux_source_directory(AI           SRC_LIST)
aux_source_directory(finance      SRC_LIST)
aux_source_directory(math         SRC_LIST)
aux_source_directory(statistics   SRC_LIST)
aux_source_directory(test         SRC_LIST)
aux_source_directory(containers   SRC_LIST)
aux_source_directory(future       SRC_LIST)
aux_source_directory(future/plot  SRC_LIST)
aux_source_directory(formating    SRC_LIST)
aux_source_directory(memory       SRC_LIST)

# directories
add_subdirectory(file)
add_subdirectory(finance)
add_subdirectory(math)
add_subdirectory(statistics)
add_subdirectory(containers)
add_subdirectory(test)
add_subdirectory(formating)
add_subdirectory(memory)

# future new feature
add_subdirectory(future)
add_subdirectory(future/plot)
add_subdirectory(future/cryptography)
add_subdirectory(AI)

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
    error/ErrorConfig.h
    memory/Ptr.h)


#===============================================================================
#           Ceres-Solver Configuration
#===============================================================================

#===============================================================================
#           Compiling
#===============================================================================

add_library(vanagandr ${SRC_LIST} ${HDRS_FILE})
link_directories(${PROJECT_BINARY_DIR})

#===============================================================================
#           test Configuration
#===============================================================================

OPTION(BUILD_TESTING "Enable tests" ON)

IF(BUILD_TESTING)
    ENABLE_TESTING()

    # Compile the gtest suite
    include_directories(${GTEST_DIR})
    include_directories("${GTEST_DIR}/include")
    add_library(gtest "${GTEST_DIR}/src/gtest-all.cc")

    MACRO(VANAGANDR_TEST NAME)
        ADD_EXECUTABLE(${NAME}_test test/${NAME}_test.cpp)
        TARGET_LINK_LIBRARIES(${NAME}_test vanagandr -isystem gtest.a -pthread)
        ADD_TEST(NAME ${NAME}_test
                 COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}_test)
    ENDMACRO(VANAGANDR_TEST)

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
    VANAGANDR_TEST(pointer)

ENDIF(BUILD_TESTING)
