static const char *MAIN_FRAG = R"(
#version 330 core

out vec4 fragColor;

void main()
{
    fragColor = vec4(0.5, 0.3, 0.1, 1.0);
}
)";