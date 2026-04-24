cmake_minimum_required(VERSION 3.25)

project(states)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(LogicLib src/logic.c)

add_executable(states src/main.c)
target_link_libraries(states PRIVATE LogicLib)

add_executable(tests tests/tests.c)
target_link_libraries(tests PRIVATE LogicLib)



