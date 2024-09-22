#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 0) in vec2 aUV;

out vec2 uv;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	uv = aUV;
}
