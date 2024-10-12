cmake_minimum_required(VERSION 3.0)
project(sylar)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -fsanitize=address -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(./)
include_directories(./thirdpart/include)

set(LIB_SRC
    sylar/log.cpp
    sylar/util.cpp
    sylar/config.cpp
    sylar/thread.cpp
    sylar/fiber.cpp
    sylar/scheduler.cpp
    sylar/iomanager.cpp
    sylar/timer.cpp
    sylar/hook.cpp
    sylar/fd_manager.cpp
    sylar/address.cpp
    sylar/socket.cpp
    sylar/socket_stream.cpp
    sylar/bytearray.cpp
    sylar/tcp_server.cpp
    sylar/stream.cpp
    sylar/http/http.cpp
    sylar/http/http_parser.cpp
    sylar/http/http11_parser.rl.cpp
    sylar/http/httpclient_parser.rl.cpp
    sylar/http/http_session.cpp
    sylar/http/http_connection.cpp
    sylar/http/http_server.cpp
    sylar/http/http_servlet.cpp
    )

ragelmaker(sylar/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar/http)
ragelmaker(sylar/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar/http)
ragelmaker(sylar/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sylar)

add_library(sylar SHARED ${LIB_SRC})
force_redefine_file_macro_for(sylar) #__FILE__

find_library(YAML_PATH NAMES libyaml-cpp.a PATHS ./thirdpart/yaml/)


set(LIB_LIB
    sylar
    pthread
    ${YAML_PATH}
    )

sylar_add_executable(test "tests/test.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_config "tests/test_config.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_thread "tests/test_thread.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_util "tests/test_util.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_fiber "tests/test_fiber.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_scheduler "tests/test_scheduler.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_iomanager "tests/test_iomanager.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_hook "tests/test_hook.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_address "tests/test_address.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_socket "tests/test_socket.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_bytearray "tests/test_bytearray.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_http "tests/test_http.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_http_parser "tests/test_http_parser.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_tcp_server "tests/test_tcp_server.cpp" sylar "${LIB_LIB}")
sylar_add_executable(echo_server examples/echo_server.cpp sylar "${LIB_LIB}")
sylar_add_executable(test_http_server "tests/test_http_server.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_http_connection "tests/test_http_connection.cpp" sylar "${LIB_LIB}")
sylar_add_executable(test_uri "tests/test_uri.cpp" sylar "${LIB_LIB}")

sylar_add_executable(my_http_server "samples/my_http_server" sylar "${LIB_LIB}")


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
