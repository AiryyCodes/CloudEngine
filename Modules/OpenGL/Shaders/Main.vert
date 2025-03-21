static const char *MAIN_VERT = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexturePos;

out vec2 a_UV;

uniform mat4 u_Transform;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
    a_UV = a_TexturePos;
}
)";
