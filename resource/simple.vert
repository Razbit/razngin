#version 330 core

layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal_modelspace;
layout(location = 3) in vec3 vertex_tangent_modelspace;
layout(location = 4) in vec3 vertex_bitangent_modelspace;

out vec2 uv;
out vec3 vertex_position_worldspace;
out vec3 eye_direction_cameraspace;
out vec3 light_direction_cameraspace;
out vec3 normal_cameraspace;
out vec3 light_direction_tangentspace;
out vec3 eye_direction_tangentspace;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform vec3 light_position_worldspace;

void main()
{
    gl_Position = p * v * m * vec4(vertex_position_modelspace, 1);

    // position of the vertex in world space
    vertex_position_worldspace = vec4(m * vec4(vertex_position_modelspace, 1)).xyz;

    // Vector from vertex to camera, in camera space (camera is at 0,0,0 there)
    vec3 vertex_position_cameraspace = vec4(v * m * vec4(vertex_position_modelspace, 1)).xyz;
    eye_direction_cameraspace = vec3(0,0,0) - vertex_position_cameraspace;

    // Vector from vertex to light, in camera space
    vec3 light_position_cameraspace = vec4(v * vec4(light_position_worldspace, 1)).xyz;
    light_direction_cameraspace = light_position_cameraspace + eye_direction_cameraspace;

    // Normal of the vertex, in camera space
    // Scaling through model matrix fucks this up, use inverse transpose
    //normal_cameraspace = vec4(v * m * vec4(vertex_normal_modelspace, 0)).xyz;

    //from model space to camera space -> modelview matrix
    mat3 mv3 = mat3(v * m);
    vec3 vertex_tangent_cameraspace = mv3 * vertex_tangent_modelspace;
    vec3 vertex_bitangent_cameraspace = mv3 * vertex_bitangent_modelspace;
    vec3 vertex_normal_cameraspace = mv3 * vertex_normal_modelspace;

    mat3 tbn = transpose(mat3(vertex_tangent_cameraspace,
                              vertex_bitangent_cameraspace,
                              vertex_normal_cameraspace));

    light_direction_tangentspace = tbn * light_direction_cameraspace;
    eye_direction_tangentspace = tbn * eye_direction_cameraspace;

    uv = vertex_uv;
}
