cmake_minimum_required(VERSION 3.28)
project(Glad)

add_library(${PROJECT_NAME} "glad/src/gl.c") # "glad/include/glad/gl.h"

target_include_directories(${PROJECT_NAME} PUBLIC "glad/include/")
