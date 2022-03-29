#version 330 core
out vec4 glFragColor;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;
uniform vec2 u_camera_position;
uniform float u_camera_zoom;

int pixelSize = 1;
int RGBRange = 256;

vec2 getLocalSpace() {
    vec2 gp, localSpace;
    gp.x = int(gl_FragCoord.x) % pixelSize;
    gp.y = int(gl_FragCoord.y) % pixelSize;

    gp.x = floor(pixelSize / 2.) - gp.x;
    gp.y = floor(pixelSize / 2.) - gp.y;

    gp.x = gl_FragCoord.x + gp.x;
    gp.y = gl_FragCoord.y + gp.y;

    localSpace = gp /  u_size;
    //    TODO(imustend): get camera zoom working
    localSpace = localSpace + (-vec2(u_position.x, -u_position.y) + vec2(u_camera_position.x, -u_camera_position.y) - vec2(u_resolution.x/2, u_resolution.y/2)) / u_size + vec2(0., 1.);
    //    localSpace = localSpace - vec2( u_position.x/u_size.x, -u_position.y/u_size.y) + vec2(u_camera_position.x/u_size.x, -u_camera_position.y/u_size.y) - vec2(u_resolution.x/u_size.x/2, u_resolution.y/u_size.y/2) + vec2(0., 1.);
    //    localSpace = localSpace;

    return localSpace;
}

vec2 getScreenSpace() {
    vec2 gp, screenSpace;
    gp.x = int(gl_FragCoord.x) % pixelSize;
    gp.y = int(gl_FragCoord.y) % pixelSize;

    gp.x = floor(pixelSize / 2.) - gp.x;
    gp.y = floor(pixelSize / 2.) - gp.y;

    gp.x = gl_FragCoord.x + gp.x;
    gp.y = gl_FragCoord.y + gp.y;

    screenSpace = gp / u_resolution;

    return screenSpace;
}

void main(){
    vec2 localSpace = getLocalSpace();

    glFragColor = vec4(localSpace.x, localSpace.y, 0.0, 1.0);
}