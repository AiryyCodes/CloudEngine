cmake_minimum_required(VERSION 3.28)
project(Glad)

add_library(glad "glad/src/gl.c") # "glad/include/glad/gl.h"

target_include_directories(glad PUBLIC "glad/include/")