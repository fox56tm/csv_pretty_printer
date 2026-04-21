cmake_minimum_required(VERSION 3.25)
project(flight-reg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Avllib src/avlLogic.c src/avlLogic.h)

add_library(Listlib src/listLogic.c src/listLogic.h)

add_executable(avl src/avl.c)
target_link_libraries(avl PRIVATE Avllib)

add_executable(list src/list.c)
target_link_libraries(list PRIVATE Listlib)
