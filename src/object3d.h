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

/**
 * @file
 * @brief Data structure for holding data of a 3D object needed by the rendering system.
 */

/**
 * @brief Contains information related to the 3D object needed by the rendering system.
 */

struct Object3dData
{
    /** ID of the shader program used by this object */
    GLuint shader_id;

    /** ID of the diffuse lighting texture sampler */
    GLuint diffuse_id;
    /** ID of the normal map sampler */
    GLuint normal_id;
    /** ID of the specular lighting texture sampler */
    GLuint specular_id;

    /** ID of the diffuse lighting texture */
    GLuint diffuse_tex;
    /** ID of the normal map */
    GLuint normal_tex;
    /** ID of the specular texture */
    GLuint specular_tex;

    /** ID of the vertex buffer */
    GLuint vertex_buf_id;
    /** ID of the texture coordinate (uv) buffer */
    GLuint uv_buf_id;
    /** ID of the normal buffer */
    GLuint normal_buf_id;
    /** ID of the tangent buffer */
    GLuint tangent_buf_id;
    /** ID of the bitangent buffer */
    GLuint bitangent_buf_id;
    /** ID of the index buffer */
    GLuint elem_buf_id;

    /** Number of faces in the model */
    GLuint faces;

    /** An entity_info instance containing file paths and other information. */
    struct entity_info ent;
};

#endif // OBJECT3D_H
