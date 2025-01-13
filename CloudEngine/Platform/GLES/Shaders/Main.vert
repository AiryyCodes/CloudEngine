static const char *MAIN_VERT = R"(
#version 100

attribute highp vec3 a_Position;

uniform mat4 u_Transform;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
}
)";