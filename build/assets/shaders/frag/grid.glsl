#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution;
    float modaa = mod(st.x, 0.2);
    glFragColor = vec4(st.y, st.x, 0.0, 1.0);
}