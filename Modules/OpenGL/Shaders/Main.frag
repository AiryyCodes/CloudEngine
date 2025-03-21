static const char *MAIN_FRAG = R"(
#version 330 core

struct Material
{
    bool hasTexture;
    sampler2D diffuse;

    vec4 color;
};

in vec2 a_UV;

out vec4 a_FragColor;

uniform Material u_Material;

void main()
{
    if (u_Material.hasTexture)
    {
        a_FragColor = texture(u_Material.diffuse, a_UV);
    }
    else
    {
        a_FragColor = u_Material.color;
    }
}
)";
