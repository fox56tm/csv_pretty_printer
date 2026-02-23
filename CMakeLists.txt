cmake_minimum_required(VERSION 3.25)
project(csv_printer)

add_library(ListLogic ListLogic.c ListLogic.h)

add_executable(csv_tool main.c)
target_link_libraries(csv_tool PRIVATE ListLogic)
