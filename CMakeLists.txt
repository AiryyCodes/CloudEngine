cmake_minimum_required(VERSION 3.28)
project(CloudEngine CXX)

option(IOS "IOS" OFF)
option(DESKTOP "DESKTOP" ON)

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

if(IOS)
	file(GLOB_RECURSE CLOUDENGINE_IOS_SOURCES
		"CloudEngine/Platform/IOS/**.cpp"
		"CloudEngine/Platform/IOS/**.h"
		"CloudEngine/Platform/IOS/**.mm"
		"CloudEngine/Platform/GLES/**.cpp"
		"CloudEngine/Platform/GLES/**.h"
	)

	set(CMAKE_SYSTEM_NAME "Darwin")

	list(APPEND CLOUDENGINE_SOURCES ${CLOUDENGINE_IOS_SOURCES})

elseif(DESKTOP)
	file(GLOB_RECURSE CLOUDENGINE_DESKTOP_SOURCES
		"CloudEngine/Platform/Desktop/**.cpp"
		"CloudEngine/Platform/Desktop/**.h"
		"CloudEngine/Platform/OpenGL/**.cpp"
		"CloudEngine/Platform/OpenGL/**.h"
	)

	list(APPEND CLOUDENGINE_SOURCES ${CLOUDENGINE_DESKTOP_SOURCES})
endif()

foreach(header ${CLOUDENGINE_SOURCES})
    set_source_files_properties(${header} PROPERTIES LANGUAGE CXX)
endforeach()

add_library(${PROJECT_NAME} ${CLOUDENGINE_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}" PRIVATE "./")

if(IOS)
	find_library(FOUNDATION_LIBRARY Foundation)
	find_library(UIKIT_LIBRARY UIKit)

	target_link_libraries(${PROJECT_NAME} PUBLIC ${FOUNDATION_LIBRARY})
	target_link_libraries(${PROJECT_NAME} PUBLIC ${UIKIT_LIBRARY})

	add_subdirectory("ext/glfm/")
	target_link_libraries(${PROJECT_NAME} PUBLIC glfm)
elseif(DESKTOP)
	add_subdirectory("ext/glfw/")
	target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

	add_subdirectory("ext/glad/")
	target_link_libraries(${PROJECT_NAME} PUBLIC Glad)
endif()

add_subdirectory("ext/stb/")
add_subdirectory("ext/fmt/")
add_subdirectory("ext/glm/")
add_subdirectory("ext/entt/")

list(APPEND CLOUDENGINE_LIBS
    STB
    fmt
    glm
    EnTT
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${CLOUDENGINE_LIBS})

#target_link_libraries(${PROJECT_NAME} PUBLIC Glad)

#target_link_libraries(${PROJECT_NAME} PUBLIC STB)

#add_subdirectory("ext/imgui/")
#target_link_libraries(${PROJECT_NAME} PUBLIC ImGui)

#target_link_libraries(${PROJECT_NAME} PUBLIC fmt)

#target_link_libraries(${PROJECT_NAME} PUBLIC glm)

#target_link_libraries(${PROJECT_NAME} PUBLIC EnTT)

add_subdirectory("Sandbox")
