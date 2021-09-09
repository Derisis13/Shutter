cmake_minimum_required(VERSION 3.19)
project(redony C)

set(CMAKE_C_STANDARD 99)

add_executable(redony main.c timing.c timing.h
        moving.c moving.h
        shutter.h
#        moving_debug.c moving_debug.h
        )