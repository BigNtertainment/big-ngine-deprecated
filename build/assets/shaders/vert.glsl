#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    vec4 position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = position;
}