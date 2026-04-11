cmake_minimum_required(VERSION 3.25)
project(csv_printer)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(ExampleLib src/ListLogic.c )

add_executable(csv_printer src/main.c)
add_executable(test src/tests.c)

target_link_libraries(test PRIVATE ExampleLib)
target_link_libraries(csv_printer PRIVATE ExampleLib)
