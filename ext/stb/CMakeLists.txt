cmake_minimum_required(VERSION 3.28)
project(STB C)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE "include/")

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
