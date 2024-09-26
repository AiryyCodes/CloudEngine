#pragma once

const char* MAIN_VERT = R"(
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.xyz, 1.0f);
	uv = aUV;
	normal = mat3(transpose(inverse(model))) * aNormal;
	fragPos = vec3(model * vec4(aPos, 1.0f));
}
)";
