#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 u_resolution;

void main()
{
    vec4 position = vec4(0.0, 0.0, 0.0, 1.0);
//    2D projection matrix
    position.x = aPos.x / u_resolution.x;
//    fliping Y axis because thats how our enigne works
    position.y = -(aPos.y / u_resolution.y);
    position.z = aPos.z;

//    vec4 position = vec4(aPos.xyz, 1.0);


    gl_Position = position;
}