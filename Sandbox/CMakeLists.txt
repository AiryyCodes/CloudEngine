cmake_minimum_required(VERSION 3.28)
project(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES
	"src/**.cpp"
	"src/**.hpp"
)

add_executable(${PROJECT_NAME} ${SANDBOX_SOURCES})

#add_custom_target(link_target ALL COMMAND ${CMAKE_COMMAND} -E create_symlink "../resources" "${PROJECT_BINARY_DIR}/resources")

target_link_libraries(${PROJECT_NAME} PRIVATE CloudEngine)