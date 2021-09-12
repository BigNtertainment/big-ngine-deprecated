#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;

vec3 color1 = vec3(217, 101, 0);
vec3 color2 = vec3(171, 235, 255);

float RGBRange = 255.0;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 color = mix(color1/RGBRange, color2/RGBRange, st.y);
    glFragColor = vec4(color, 1.0);
}