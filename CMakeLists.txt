cmake_minimum_required(VERSION 3.28)
project(CloudEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CLOUDENGINE_SOURCES
	"CloudEngine/**.cpp"
	"CloudEngine/**.h"
)

foreach(header ${CLOUDENGINE_SOURCES})
    set_source_files_properties(${header} PROPERTIES LANGUAGE CXX)
endforeach()

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} ${CLOUDENGINE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}" PRIVATE "./")

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
