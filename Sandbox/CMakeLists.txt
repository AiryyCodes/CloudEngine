cmake_minimum_required(VERSION 3.28)
project(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES
	"src/**.cpp"
	"src/**.hpp"
)

add_executable(${PROJECT_NAME} ${SANDBOX_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE CloudEngine)
