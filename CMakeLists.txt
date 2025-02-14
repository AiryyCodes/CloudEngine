cmake_minimum_required(VERSION 3.28)
project(CloudEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Modules")

file(GLOB CLOUDENGINE_SOURCES
	"Engine/*.cpp"
	"Engine/Renderer/*.cpp"
	"Engine/Scene/*.cpp"
	"Engine/Window/*.cpp"
	"Engine/Module/*.cpp"
)

file(GLOB_RECURSE CLOUDENGINE_DESKTOP_SOURCES
	"Engine/Platform/Desktop/**.cpp"
)

# file(GLOB_RECURSE MODULE_SOURCES
	# "Modules/**.cpp"
# )

list(APPEND CLOUDENGINE_SOURCES ${CLOUDENGINE_DESKTOP_SOURCES})
# list(APPEND CLOUDENGINE_SOURCES ${MODULE_SOURCES})

foreach(header ${CLOUDENGINE_SOURCES})
    set_source_files_properties(${header} PROPERTIES LANGUAGE CXX)
endforeach()

add_library(${PROJECT_NAME} ${CLOUDENGINE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}" PRIVATE "./" PRIVATE ${MODULES_DIR})


file(GLOB modules RELATIVE ${MODULES_DIR} "${MODULES_DIR}/*")

foreach(module ${modules})
	if(IS_DIRECTORY "${MODULES_DIR}/${module}")
		#target_include_directories(${PROJECT_NAME} PUBLIC "${MODULES_DIR}/${module}")
		add_subdirectory("${MODULES_DIR}/${module}")
		target_link_libraries(${PROJECT_NAME} PUBLIC ${module})
	endif()
endforeach()


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
