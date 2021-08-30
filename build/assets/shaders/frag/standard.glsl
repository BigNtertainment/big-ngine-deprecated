#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;


void main(){
//    FIXME(tymon): PENIS PENIS PENIS
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec2 zt = (st - u_position/u_resolution) / (u_size/u_resolution);
    glFragColor = vec4(zt.x,zt.y,0.0,1.0);
}

