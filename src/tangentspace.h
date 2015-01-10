#ifndef TANGENTSPACE_H
#define TANGENTSPACE_H

#include <vector>

void computeTangentBasis(
    std::vector<glm::vec3> & vertices,
    std::vector<glm::vec2> & uvs,
    std::vector<glm::vec3> & normals,
    std::vector<glm::vec3> & tangents,
    std::vector<glm::vec3> & bitangents
);

#endif // TANGENTSPACE_H
