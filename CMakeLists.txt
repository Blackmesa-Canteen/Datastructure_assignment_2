cmake_minimum_required(VERSION 3.17)
project(Assiginment2_Code C)
set(CMAKE_C_STANDARD 99)

add_executable(Assiginment2_Code main.c dictFunctions.c list.c dictFunctions.h list.h pointFunctions.c pointFunctions.h kdTree.h kdTree.c findClosest.c findClosest.h)
target_link_libraries(Assiginment2_Code C)