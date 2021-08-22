#version 330 core
out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution;
    FragColor = vec4(st.x, abs(sin(u_time)), st.y, 1.0f);
}
