cmake_minimum_required(VERSION 3.19)
project(redony_automata C)

set(CMAKE_C_STANDARD 99)

add_executable(redony_automata main.c timing.c timing.h
        moving.c moving.h
        shutter.h
        #mozgatas_demo.c mozgatas_demo.h
        )