cmake_minimum_required(VERSION 3.28)
project(ImGui)

file(GLOB_RECURSE IMGUI_SOURCES
	"src/**.cpp"
)

# include_directories("include/")
add_library(ImGui ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC "include/")
