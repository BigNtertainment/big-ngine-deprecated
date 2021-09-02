#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 u_resolution;
uniform vec2 u_position;

void main()
{
//  transormation math
    gl_Position.x = ((aPos.x + u_position.x) / u_resolution.x*2) - 1;

    gl_Position.y = ((-aPos.y - u_position.y) / u_resolution.y*2) + 1;

    gl_Position.z = aPos.z;

    gl_Position.w = 1.0;
}