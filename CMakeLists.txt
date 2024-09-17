cmake_minimum_required(VERSION 3.28)
project(CloudEngine CXX)

add_compile_definitions(RENDER_BACKEND="OpenGL")
add_compile_definitions(DISPLAY_ENVIRONMENT="Wayland")

file(GLOB_RECURSE CLOUD_SOURCE "src/**.cpp")

add_library(${PROJECT_NAME} ${CLOUD_SOURCE})
target_include_directories(${PROJECT_NAME}
                           PUBLIC "${PROJECT_SOURCE_DIR}/include/")

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
