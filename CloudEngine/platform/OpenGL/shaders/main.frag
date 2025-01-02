static const char *MAIN_FRAG = R"(
#version 410 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.5f, 0.3f, 0.1f, 1.0f);
}
)";