#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution;
    glFragColor = vec4(st.x,st.y,0.0,1.0);
}

