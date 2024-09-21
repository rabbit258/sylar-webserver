cmake_minimum_required(VERSION 3.0)
project(sylar)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(./)
include_directories(./thirdpart/include)

set(LIB_SRC
    sylar/log.cpp
    sylar/util.cpp
    sylar/config.cpp
    sylar/thread.cpp
    sylar/fiber.cpp
    )
add_library(sylar SHARED ${LIB_SRC})
force_redefine_file_macro_for(sylar) #__FILE__

find_library(YAML_PATH NAMES libyaml-cpp.a PATHS ./thirdpart/yaml/)

set(LIB_LIB
    sylar
    pthread
    ${YAML_PATH}
    )

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
force_redefine_file_macro_for(test) #__FILE__
target_link_libraries(test ${LIB_LIB})

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config sylar)
force_redefine_file_macro_for(test_config) #__FILE__
target_link_libraries(test_config ${LIB_LIB})

add_executable(test_thread tests/test_thread.cpp)
add_dependencies(test_thread sylar)
force_redefine_file_macro_for(test_thread) #__FILE__
target_link_libraries(test_thread ${LIB_LIB})

add_executable(test_util tests/test_util.cpp)
add_dependencies(test_util sylar)
force_redefine_file_macro_for(test_util) #__FILE__
target_link_libraries(test_util ${LIB_LIB})

add_executable(test_fiber tests/test_fiber.cpp)
add_dependencies(test_fiber sylar)
force_redefine_file_macro_for(test_fiber) #__FILE__
target_link_libraries(test_fiber ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)