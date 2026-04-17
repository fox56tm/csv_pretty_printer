cmake_minimum_required(VERSION 3.25)
project(avl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(ExampleLib src/avlLogic.c)

add_executable(avl src/main.c)
target_link_libraries(avl PRIVATE ExampleLib)
