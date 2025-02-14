project(OpenGL)

file(GLOB_RECURSE OPENGL_SOURCES
	"**.cpp"
)

add_library(${PROJECT_NAME} ${OPENGL_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "./" PRIVATE "../../")

target_link_libraries(${PROJECT_NAME} PRIVATE CloudEngine glfw)
