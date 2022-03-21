#version 330 core
out vec4 glFragColor;

in vec2 TexCoord;

uniform vec3 u_color;

uniform sampler2D Texture;


void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Texture, TexCoord).r);
    glFragColor = vec4(u_color, 1.0) * sampled;
}
