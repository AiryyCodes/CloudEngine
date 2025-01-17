static const char *MAIN_FRAG = R"(
#version 330 core

in vec2 texPos;

out vec4 fragColor;

uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, texPos);
    // fragColor = vec4(0.5, 0.3, 0.1, 1.0);
}
)";