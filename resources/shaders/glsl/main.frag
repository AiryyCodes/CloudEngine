#version 330 core

struct Material
{
	sampler2D diffuse;
};

out vec4 FragColor;

in vec2 uv;

uniform sampler2D tex;
uniform Material material;

void main()
{
	FragColor = texture(material.diffuse, uv);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
