cmake_minimum_required(VERSION 3.28)
project(STB C)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE "include/")

set_target_properties(stb PROPERTIES LINKER_LANGUAGE C)
