#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;

vec2 sp;
int pixelSize = 5;
int RGBRange = 256;

vec3 starColor = vec3(211., 255, 252) / RGBRange;


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

    float pct = .0;
    pct = smoothstep(0.0, 1., -distance(st,vec2(0.5, 0.2)) * 100 + 1.);
    pct += smoothstep(0.0, 1., -distance(st,vec2(0.525)) * 200 + 1.);


    vec3 color = vec3(pct * starColor);
    glFragColor = vec4(color,1.0);
}