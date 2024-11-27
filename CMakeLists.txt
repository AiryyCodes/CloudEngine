cmake_minimum_required(VERSION 3.28)
project(CloudEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CLOUDENGINE_SOURCES
	"CloudEngine/core/**.cpp"
	"CloudEngine/core/**.h"
	"CloudEngine/platform/**.cpp"
	"CloudEngine/platform/**.h"
)

add_library(${PROJECT_NAME} ${CLOUDENGINE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "./")

add_subdirectory("ext/glfw/")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory("ext/glad/")
target_link_libraries(${PROJECT_NAME} PUBLIC Glad)

add_subdirectory("ext/stb/")
target_link_libraries(${PROJECT_NAME} PUBLIC STB)

add_subdirectory("ext/imgui/")
target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)

add_subdirectory("ext/fmt/")
target_link_libraries(${PROJECT_NAME} PUBLIC fmt)

add_subdirectory("ext/glm/")
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

add_subdirectory("Sandbox")
