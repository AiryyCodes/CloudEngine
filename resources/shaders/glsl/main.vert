#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 0) in vec2 aUV;

out vec2 uv;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	uv = aUV;
}
