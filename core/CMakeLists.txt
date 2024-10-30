cmake_minimum_required(VERSION 3.28)
project(Core)

file(GLOB_RECURSE CORE_SOURCES
	"src/**.cpp"
	"src/**.h"
)

add_library(core ${CORE_SOURCES})
target_include_directories(core PUBLIC "include/")

target_link_libraries(core PRIVATE backend_opengl)

target_link_libraries(core PUBLIC glfw glm::glm)
