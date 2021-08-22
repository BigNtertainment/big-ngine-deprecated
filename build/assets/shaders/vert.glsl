#version 330 core
layout (location = 0) in vec3 aPos;

uniform float u_time;

void main()
{
    vec2 cen = vec2(0.0f, 0.0f);
    float s = sin(u_time);
    float c = cos(u_time);
    
    vec4 position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    position.x -= cen.x;
    position.y -= cen.y;

    float xnew = position.x * c - position.y * s;
    float ynew = position.x * s + position.y * c;

    position.x = xnew + cen.x;
    position.y = ynew + cen.y;


    gl_Position = position;
}