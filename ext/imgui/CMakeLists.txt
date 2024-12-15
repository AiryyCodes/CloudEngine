cmake_minimum_required(VERSION 3.28)
project(ImGui)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE IMGUI_SOURCES
	"src/**.cpp"
)

# include_directories("include/")
add_library(ImGui ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC "include/")

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
