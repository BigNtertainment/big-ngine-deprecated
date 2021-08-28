#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;

void main(){
    //FIXME: WHAT THE FUCK
    vec2 st = gl_FragCoord.xy/u_resolution;
    float modaa = mod(st.x, 0.1);
    glFragColor = vec4(st.x, step(1.0, modaa), 0.0, 1.0);
}