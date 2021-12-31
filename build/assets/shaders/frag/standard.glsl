#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;

vec2 sp;
int pixelSize = 5;
int RGBRange = 256;
vec3 color = vec3(91, 127, 78) / RGBRange;

void main(){
    sp.x = int(gl_FragCoord.x) % pixelSize;
    sp.y = int(gl_FragCoord.y) % pixelSize;

    sp.x = floor(pixelSize / 2.) - sp.x;
    sp.y = floor(pixelSize / 2.) - sp.y;

    sp.x = gl_FragCoord.x + sp.x;
    sp.y = gl_FragCoord.y + sp.y;

    //  :heart: falj2
    vec2 st = vec2(
    (sp.x/ u_size.x) - 1/(u_size.x / u_position.x),
    (sp.y/ u_size.y) - ((u_resolution.y / u_size.y) - 1. - (u_position.y / u_size.y))
    );

    glFragColor = vec4(color,1.0);
}