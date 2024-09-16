cmake_minimum_required(VERSION 2.0)
project(sylar)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(./)
include_directories(./thirdpart/include)

set(LIB_SRC
    sylar/log.cpp
    sylar/util.cpp
    sylar/config.cpp
    )
add_library(sylar SHARED ${LIB_SRC})



find_library(YAML_PATH NAMES libyaml-cpp.a PATHS ./thirdpart/yaml/)

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
target_link_libraries(test sylar ${YAML_PATH})

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config sylar)
target_link_libraries(test_config sylar ${YAML_PATH})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)