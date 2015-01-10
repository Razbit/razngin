#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

bool load_obj(
        const char* path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals
);

#endif // OBJLOADER_H
