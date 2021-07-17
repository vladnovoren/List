cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

set(FLAGS "-Wall -Wextra -g")

project(list)
add_executable(list src/main.cpp src/list.cpp)
add_executable(test src/test.cpp)
target_include_directories(list PUBLIC include)

set_target_properties(list test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)