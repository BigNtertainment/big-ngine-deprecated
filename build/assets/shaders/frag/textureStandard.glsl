#version 330 core
out vec4 glFragColor;

in vec2 TexCoord;

uniform vec2 u_resolution;
uniform vec2 u_size;
uniform vec2 u_position;


uniform sampler2D Texture;


void main() {
    glFragColor = texture(Texture, TexCoord);
}
