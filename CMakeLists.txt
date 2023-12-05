cmake_minimum_required(VERSION 3.26)
project(2048enC C)

set(CMAKE_C_STANDARD 23)

add_executable(2048enC main.c
        functions.c
        functions.h)
