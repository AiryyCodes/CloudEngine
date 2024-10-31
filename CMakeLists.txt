cmake_minimum_required(VERSION 3.28)
project(CloudEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CLOUD_ENGINE_RESOURCES_PATH "${PROJECT_SOURCE_DIR}/resources" CACHE INTERNAL "Path to internal cloud engine resources")
set(CLOUD_ENGINE_BACKEND "OpenGL")

set(ASSIMP_WARNINGS_AS_ERRORS OFF)

#file(GLOB_RECURSE CLOUD_SOURCE "src/**.cpp")

#include_directories("${PROJECT_SOURCE_DIR}/include/")
#add_library(${PROJECT_NAME} ${CLOUD_SOURCE})
#target_include_directories(${PROJECT_NAME}
#                          PUBLIC "${PROJECT_SOURCE_DIR}/include/")
#target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/resources/shaders/")

find_package(glfw3 REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory("ext/glad2")
# target_link_libraries(${PROJECT_NAME} PUBLIC glad)

add_subdirectory("ext/stb")
# target_link_libraries(${PROJECT_NAME} PUBLIC stb)

find_package(glm REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

find_package(assimp REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC assimp)

add_subdirectory("ext/fmt")
add_subdirectory("ext/imgui")

add_subdirectory("core/")
add_subdirectory("backends/")
add_subdirectory("editor/")
