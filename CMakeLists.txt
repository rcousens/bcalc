cmake_minimum_required(VERSION 3.2)
project(binary_calc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES main.c)
add_executable(binary_calc ${SOURCE_FILES} command.h command.c completion.h completion.c)
target_link_libraries(binary_calc readline)