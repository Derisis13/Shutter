cmake_minimum_required(VERSION 3.19)
project(redony_automata C)

set(CMAKE_C_STANDARD 99)

add_executable(redony_automata main.c idozites.c idozites.h
        #mozgatas.c mozgatas.h
        redony.h
        mozgatas_demo.c mozgatas_demo.h
        )