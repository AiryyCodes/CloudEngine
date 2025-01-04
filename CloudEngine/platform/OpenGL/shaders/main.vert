static const char *MAIN_VERT = R"(
#version 410 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_Transform;
uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
    gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0f);
} 
)";