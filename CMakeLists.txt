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

add_executable(test_scheduler tests/test_scheduler.cpp)
add_dependencies(test_scheduler sylar)
force_redefine_file_macro_for(test_scheduler) #__FILE__
target_link_libraries(test_scheduler ${LIB_LIB})

add_executable(test_iomanager tests/test_iomanager.cpp)
add_dependencies(test_iomanager sylar)
force_redefine_file_macro_for(test_iomanager) #__FILE__
target_link_libraries(test_iomanager ${LIB_LIB})

add_executable(test_hook tests/test_hook.cpp)
add_dependencies(test_hook sylar)
force_redefine_file_macro_for(test_hook) #__FILE__
target_link_libraries(test_hook ${LIB_LIB})

add_executable(test_address tests/test_address.cpp)
add_dependencies(test_address sylar)
force_redefine_file_macro_for(test_address) #__FILE__
target_link_libraries(test_address ${LIB_LIB})

add_executable(test_socket tests/test_socket.cpp)
add_dependencies(test_socket sylar)
force_redefine_file_macro_for(test_socket) #__FILE__
target_link_libraries(test_socket ${LIB_LIB})

add_executable(test_bytearray tests/test_bytearray.cpp)
add_dependencies(test_bytearray sylar)
force_redefine_file_macro_for(test_bytearray) #__FILE__
target_link_libraries(test_bytearray ${LIB_LIB})

add_executable(test_http tests/test_http.cpp)
add_dependencies(test_http sylar)
force_redefine_file_macro_for(test_http) #__FILE__
target_link_libraries(test_http ${LIB_LIB})

add_executable(test_http_parser tests/test_http_parser.cpp)
add_dependencies(test_http_parser sylar)
force_redefine_file_macro_for(test_http_parser) #__FILE__
target_link_libraries(test_http_parser ${LIB_LIB})

add_executable(test_tcp_server tests/test_tcp_server.cpp)
add_dependencies(test_tcp_server sylar)
force_redefine_file_macro_for(test_tcp_server) #__FILE__
target_link_libraries(test_tcp_server ${LIB_LIB})

add_executable(echo_server examples/echo_server.cpp)
add_dependencies(echo_server sylar)
force_redefine_file_macro_for(echo_server) #__FILE__
target_link_libraries(echo_server ${LIB_LIB})

add_executable(test_http_server tests/test_http_server.cpp)
add_dependencies(test_http_server sylar)
force_redefine_file_macro_for(test_http_server) #__FILE__
target_link_libraries(test_http_server ${LIB_LIB})

add_executable(test_http_connection tests/test_http_connection.cpp)
add_dependencies(test_http_connection sylar)
force_redefine_file_macro_for(test_http_connection) #__FILE__
target_link_libraries(test_http_connection ${LIB_LIB})

add_executable(test_uri tests/test_uri.cpp)
add_dependencies(test_uri sylar)
force_redefine_file_macro_for(test_uri) #__FILE__
target_link_libraries(test_uri ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)