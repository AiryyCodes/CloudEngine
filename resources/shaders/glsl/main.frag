#pragma once

const char* MAIN_FRAG = R"(
#version 330 core

struct Material
{
	sampler2D diffuse;
};

out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D tex;
uniform Material material;

uniform vec3 lightPos;

void main()
{
	vec3 lightColor = vec3(0.5f, 1.0f, 1.0f);
	vec3 objectColor = vec3(1.0f, 0.0f, 1.0f);

	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;

	FragColor = vec4(result, 1.0f);
	//FragColor = texture(material.diffuse, uv);
    //FragColor = vec4(1.0f, 0.5f, 0.i2f, 1.0f);
}
)";
