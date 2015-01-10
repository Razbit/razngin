#version 330 core

in vec2 uv;

out vec4 color;

uniform sampler2D texture_sampler;
uniform vec4 in_color;


void main()
{
    color = vec4(in_color * abs(texture2D(texture_sampler, uv).x - 1.0f));
}
