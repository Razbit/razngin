#version 330 core

in vec2 uv;
in vec3 vertex_position_worldspace;
in vec3 eye_direction_cameraspace;
in vec3 light_direction_cameraspace;

in vec3 light_direction_tangentspace;
in vec3 eye_direction_tangentspace;

out vec4 color;

uniform sampler2D diffuse_texture_sampler;
uniform sampler2D normal_texture_sampler;
uniform sampler2D specular_texture_sampler;
uniform vec3 light_position_worldspace;
uniform float light_power;
uniform vec3 light_color;
uniform mat4 m;
uniform mat4 v;

void main()
{
    float distance = length(light_position_worldspace - vertex_position_worldspace);

    // material properties
    vec3 material_diffuse_color = texture2D(diffuse_texture_sampler, uv).rgb;
    vec3 material_ambient_color = vec3(0.1, 0.1, 0.1) * material_diffuse_color;
    vec3 material_specular_color = texture2D(specular_texture_sampler, uv).rgb * 0.3;

    // Diffuse
    // Normal of the computed fragment, in camera space
    vec3 n = normalize(texture2D(normal_texture_sampler, vec2(uv.x, -uv.y)).rgb * 2.0 - 1.0);

    // Direction of the light (from the fragment to the light)
    vec3 l = normalize(light_direction_tangentspace);
    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float cos_theta = clamp(dot(n, l), 0, 1);

    vec3 diffuse = material_diffuse_color * light_color * light_power * cos_theta / (distance * distance);

    // Specular
    // Eye vector (towards camera)
    vec3 e = normalize(eye_direction_tangentspace);
    // Direction to which triangle reflects light
    vec3 r = reflect(-l, n);
    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cos_alpha = clamp(dot(e, r), 0, 1);

    vec3 specular = material_specular_color * light_color * light_power * pow(cos_alpha, 5) / (distance * distance);

    color.xyz = material_ambient_color + diffuse + specular;
    color.a = 0.5;
}
