file(GLOB_RECURSE OPENGL_BACKEND_SOURCES
	"**.cpp"
	"**.h"
	"shaders/**.vert"
	"shaders/**.frag"
)

add_library(backend_opengl ${OPENGL_BACKEND_SOURCES})
target_include_directories(backend_opengl PUBLIC "./")

target_link_libraries(backend_opengl PRIVATE core glad stb assimp ImGui)
