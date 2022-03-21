#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;
uniform vec2 u_camera_position;

vec4 color = vec4(1.);
vec2 pitch = vec2(100., 100.);

void main(){
    if (mod(gl_FragCoord.x, pitch[0]) < 1. ||
    mod(gl_FragCoord.y, pitch[1]) < 1.) {
        glFragColor = color;
    } else {
        glFragColor = vec4(0.);
    }
}