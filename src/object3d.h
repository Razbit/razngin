/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

/* Object3d defines a 3D object, includes its vertex, uv, normal etc handles,
 * shaders, textures.. */
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "entityinfo.h"

#ifndef OBJECT3D_H
#define OBJECT3D_H

struct Object3dData
{
    GLuint shader_id;

    GLuint diffuse_id;
    GLuint normal_id;
    GLuint specular_id;

    GLuint diffuse_tex;
    GLuint normal_tex;
    GLuint specular_tex;

    GLuint vertex_buf_id;
    GLuint uv_buf_id;
    GLuint normal_buf_id;
    GLuint tangent_buf_id;
    GLuint bitangent_buf_id;
    GLuint elem_buf_id;

    GLuint faces;

    struct entity_info ent;
};

#endif // OBJECT3D_H
