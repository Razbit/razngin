#ifndef VBOINDEXER_H
#define VBOINDEXER_H

#include <vector>
#include <glm/glm.hpp>

/**
 * @file
 * @brief Index the VBO.
 */

/**
 * @brief Index the VBO.
 */

void indexVBO(
    std::vector<glm::vec3> & in_vertices,
    std::vector<glm::vec2> & in_uvs,
    std::vector<glm::vec3> & in_normals,

    std::vector<unsigned short> & out_indices,
    std::vector<glm::vec3> & out_vertices,
    std::vector<glm::vec2> & out_uvs,
    std::vector<glm::vec3> & out_normals
);

/**
 * @brief Index the VBO containing the Tangent-Bitangent-Normal info.
 */
void indexVBO_TBN(
    std::vector<glm::vec3> & in_vertices,
    std::vector<glm::vec2> & in_uvs,
    std::vector<glm::vec3> & in_normals,
    std::vector<glm::vec3> & in_tangents,
    std::vector<glm::vec3> & in_bitangents,

    std::vector<unsigned short> & out_indices,
    std::vector<glm::vec3> & out_vertices,
    std::vector<glm::vec2> & out_uvs,
    std::vector<glm::vec3> & out_normals,
    std::vector<glm::vec3> & out_tangents,
    std::vector<glm::vec3> & out_bitangents
);

#endif // VBOINDEXER_H
