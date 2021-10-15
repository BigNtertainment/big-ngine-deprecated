///bassicly the same as standard.glsl but it doesnt care about camera

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec2 u_resolution;
uniform vec2 u_position;
uniform vec2 u_size;
uniform float u_depth;
uniform float u_rotation;

#define PI 3.14159265359

void main()
{
    //  ranslation matrix
    //  the aPos is 1 or 0 for every point in squre so i know if i should add size to the point or not
    mat4 translationMatrix = mat4(
    1.0, 0.0, 0.0, u_position.x + 0.5 * u_size.x,
    0.0, 1.0, 0.0, u_position.y + 0.5 * u_size.y,
    0.0, 0.0, 1.0, u_depth,
    0.0, 0.0, 0.0, 1.0
    );

    //  scaling matrinx
    mat4 projectionMatrix = mat4(
    1/(0.5*u_resolution.x), 0.0, 0.0, 0.0,
    0.0, -1/(0.5*u_resolution.y), 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
    );

    mat4 rotationMatrix = mat4(
    cos(u_rotation * PI / 180), -sin(u_rotation * PI / 180), 0.0, 0.0,
    sin(u_rotation * PI / 180), cos(u_rotation * PI / 180), 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
    );


    //  outputing point position
    gl_Position = vec4(aPos.xy * u_size + vec2(-0.5 * u_size.x, -0.5 * u_size.y), 0.0, 1.0)
    * rotationMatrix * translationMatrix * projectionMatrix;


    //  outputing texture coordinets
    TexCoord = aTexCoord;
}

