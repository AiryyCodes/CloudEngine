project(OpenGL)

file(GLOB_RECURSE OPENGL_SOURCES
	"${PROJECT_SOURCE_DIR}/**.cpp"
)

add_library(${PROJECT_NAME} STATIC ${OPENGL_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "../")

find_package(OpenGL REQUIRED)

add_subdirectory(../../ext/glad OpenGL/Glad)

target_link_libraries(${PROJECT_NAME} PRIVATE
	CloudEngine
	Glad
	OpenGL::GL
)
