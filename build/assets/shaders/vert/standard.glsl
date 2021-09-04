#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 u_resolution;
uniform vec2 u_position;
uniform float u_depth;

void main()
{
//  transormation math
    mat4 transformationMatrix = mat4(
    1/(2*u_resolution.x), 0.0, 0.0, u_position.x,
    0.0, 1/(2*u_resolution.y), 0.0, u_position.y,
    0.0, 0.0, 1.0, u_depth,
    0.0, 0.0, 0.0, 1.0
    );
    vec4 basePos = vec4(aPos, 1.0);

    gl_Position.x = ((aPos.x + u_position.x) / u_resolution.x*2) - 1;

    gl_Position.y = ((-aPos.y - u_position.y) / u_resolution.y*2) + 1;

    gl_Position.z = u_depth;

    gl_Position.w = 1.0;

//    gl_Position = transformationMatrix * basePos;
}