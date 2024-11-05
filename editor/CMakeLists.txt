cmake_minimum_required(VERSION 3.28)
project(Editor)

file(GLOB_RECURSE EDITOR_SOURCES
	"src/**.cpp"
	"src/**.h"
)

add_executable(${PROJECT_NAME} ${EDITOR_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "src/")
target_include_directories(${PROJECT_NAME} PUBLIC "include/")

target_link_libraries(${PROJECT_NAME} PRIVATE core)
