cmake_minimum_required(VERSION 3.0)
project(reactor_common)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -flto")

set(DEPENDENCY_DIR "${CMAKE_SOURCE_DIR}/ext")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(Catch)

set(SOURCE_FILES
        )

set(TEST_SOURCE_FILES
        test/unit/reactor/common/commonTest.cpp
        test/unit/reactor/common/main.cpp)

include_directories(
        "${Catch_INCLUDE_DIR}"
        ../reactor-api-common/api/include)

#add_executable(reactor_common ${SOURCE_FILES})
add_executable(reactor_common_test ${SOURCE_FILES} ${TEST_SOURCE_FILES})