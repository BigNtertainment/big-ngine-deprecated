#version 330 core
layout (location = 0) in vec3 aPos;

uniform float u_time;

void main()
{
    vec2 c = vec2(0.0f, 0.0f);
//    float s = sin(u_time);
//    float c = cos(u_time);
//    float s = sin(90.0f);
//    float c = cos(90.0f);
    vec4 position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    position.x -= c.x;
    position.y -= c.y;
//
//    float xnew = position.x * c - position.y * s;
//    float ynew = position.x * s + position.y * c;
//
//    position.x = xnew + c.x;
//    position.y = ynew + c.y;


    gl_Position = position;
}