cmake_minimum_required(VERSION 3.28)
project(CloudEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB CLOUDENGINE_SOURCES
	"CloudEngine/*.cpp"
	"CloudEngine/*.h"
	"CloudEngine/Renderer/*.cpp"
	"CloudEngine/Renderer/*.h"
	"CloudEngine/Scene/*.cpp"
	"CloudEngine/Scene/*.h"
	"CloudEngine/Window/*.cpp"
	"CloudEngine/Window/*.h"
)

file(GLOB_RECURSE CLOUDENGINE_DESKTOP_SOURCES
	"CloudEngine/Platform/Desktop/**.cpp"
	"CloudEngine/Platform/Desktop/**.h"
	"CloudEngine/Platform/OpenGL/**.cpp"
	"CloudEngine/Platform/OpenGL/**.h"
)

list(APPEND CLOUDENGINE_SOURCES ${CLOUDENGINE_DESKTOP_SOURCES})

foreach(header ${CLOUDENGINE_SOURCES})
    set_source_files_properties(${header} PROPERTIES LANGUAGE CXX)
endforeach()

add_library(${PROJECT_NAME} ${CLOUDENGINE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}" PRIVATE "./")

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

#add_subdirectory("ext/glfw/")
add_subdirectory("ext/glad/")
add_subdirectory("ext/stb/")
add_subdirectory("ext/fmt/")
add_subdirectory("ext/glm/")
add_subdirectory("ext/entt/")

list(APPEND CLOUDENGINE_LIBS
    STB
    fmt
    glm
    EnTT
	Glad
	glfw
	OpenGL::GL
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${CLOUDENGINE_LIBS})

add_subdirectory("Sandbox")
