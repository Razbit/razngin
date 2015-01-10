#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <objloader.h>

extern FILE* logfp;
extern FILE* errlog;

bool load_obj(const char* path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals
){
    fprintf(logfp, "Loading model: %s\n", path);

    std::vector<unsigned int> vertex_indices, uv_indices, norm_indices;
    std::vector<glm::vec3> tmp_vertices;
    std::vector<glm::vec2> tmp_uvs;
    std::vector<glm::vec3> tmp_norms;

    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        fprintf(errlog, "File not found: %s\n", path);
        return false;
    }

    while(1)
    {
        char header[128];
        if (fscanf(fp, "%s", header) == EOF)
            break;
        if (strcmp(header, "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tmp_vertices.push_back(vertex);
        }
        else if (strcmp(header, "vt") == 0)
        {
            glm::vec2 uv;
            fscanf(fp, "%f %f\n", &uv.x, &uv.y);
            tmp_uvs.push_back(uv);
        }
        else if (strcmp(header, "vn") == 0)
        {
            glm::vec3 norm;
            fscanf(fp, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
            tmp_norms.push_back(norm);
        }
        else if (strcmp(header, "f") == 0)
        {
            unsigned int vertex_index[3], uv_index[3], norm_index[3];
            int matches = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vertex_index[0], &uv_index[0], &norm_index[0],
                                 &vertex_index[1], &uv_index[1], &norm_index[1],
                                 &vertex_index[2], &uv_index[2], &norm_index[2]
            );
            if (matches != 9)
            {
                fprintf(errlog, "Parsing failed: %s\n", path);
                return false;
            }
            vertex_indices.push_back(vertex_index[0]);
            vertex_indices.push_back(vertex_index[1]);
            vertex_indices.push_back(vertex_index[2]);
            uv_indices.push_back(uv_index[0]);
            uv_indices.push_back(uv_index[1]);
            uv_indices.push_back(uv_index[2]);
            norm_indices.push_back(norm_index[0]);
            norm_indices.push_back(norm_index[1]);
            norm_indices.push_back(norm_index[2]);
        }
        else
        {
            /* comment, perhaps? */
            char buf[1000];
            fgets(buf, 1000, fp);
        }
    }

    /* Alright, time for indexing.. */

    /* For each vertex of each triangle */
    for (unsigned int i = 0; i < vertex_indices.size(); i++)
    {
        /* Get the indices of the vertex' attributes */
        unsigned int vertex_index = vertex_indices[i];
        unsigned int uv_index = uv_indices[i];
        unsigned int norm_index = norm_indices[i];

        /* Get its attributes */
        glm::vec3 vertex = tmp_vertices[vertex_index - 1];
        glm::vec2 uv = tmp_uvs[uv_index - 1];
        glm::vec3 norm = tmp_norms[norm_index - 1];

        /* Buffer the attribs */
        out_vertices.push_back(vertex);
        out_uvs.push_back(uv);
        out_normals.push_back(norm);
    }

    fclose(fp);
    return true;
}

