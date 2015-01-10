#version 330 core

layout(location = 0) in vec2 vertex_pos_screenspace;
layout(location = 1) in vec2 vertex_uv;

out vec2 uv;

void main()
{
    // Output position in clip space (map [0..800][0..600] to [-1..1][-1..1]
    vec2 vertexpos_homogeneous = vertex_pos_screenspace - vec2(400, 300);
    vertexpos_homogeneous /= vec2(400, 300);

    gl_Position = vec4(vertexpos_homogeneous, 0, 1);

    uv = vertex_uv;
}
