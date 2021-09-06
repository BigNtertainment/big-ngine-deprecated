#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;


void main(){
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec2 zt = vec2(0.0, 0.0);
    zt.x = (st.x - u_position.x/u_resolution.x) / (u_size.x/u_resolution.x);
//    FIXME(tymon): Y axis is kinda fucked!! so dont use zt vector for now, i will take care of it later
    zt.y = (st.y - (1 - u_position.y/u_resolution.y - u_size.y/u_resolution.y)) / (1 - u_position.y/u_resolution.y);
    glFragColor = vec4(0.0,0.0,1.0,1.0);
}