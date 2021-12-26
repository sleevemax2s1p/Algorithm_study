cmake_minimum_required(VERSION 3.5)

project(algorithm)
SET(CMAKE_LIBRARY_OUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/out)
MESSAGE(STATUS "Static lib has been created in dir" ${CMAKE_LIBRARY_OUT_DIRECTORY})
add_library(algorithm SHARED KmpMarch.c KmpMarch.h TreeArray.h TreeArray.c)
add_executable(test test.c)
MESSAGE(STATUS "finish")