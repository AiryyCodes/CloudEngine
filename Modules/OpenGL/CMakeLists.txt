project(OpenGL)

file(GLOB_RECURSE OPENGL_SOURCES
	"${PROJECT_SOURCE_DIR}/**.cpp"
)

add_library(${PROJECT_NAME} STATIC ${OPENGL_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "../")

target_link_libraries(${PROJECT_NAME} PRIVATE CloudEngine)
