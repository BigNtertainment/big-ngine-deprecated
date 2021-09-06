#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;

vec3 color1 = vec3(217/255.0, 101/255.0, 0/255.0);
vec3 color2 = vec3(171/255.0, 235/255.0, 255/255.0);

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 color = mix(color1, color2, st.y);
    glFragColor = vec4(color, 1.0);
}