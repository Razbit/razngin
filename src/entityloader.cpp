
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <soil/SOIL.h>

#include "scene.h"
#include "vboindexer.h"
#include "object3d.h"
#include "entityloader.h"
#include "tangentspace.h"

struct entity_info EntityLoader::parse_file(const char* path)
{
    log.write("Parsing block information from '%s'\n", path);

    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        log.write("  Parsing failed!\n");
        exit(EXIT_FAILURE);
    }

    struct entity_info info;

    while(1)
    {
        char buf[100];
        char buf2[500];
        if (fscanf(file, "%s %s\n", buf, buf2) == EOF)
            break;
        if (buf[0] == '#') // comment
            continue;
        if (strcmp(buf, "vertex:") == 0)
            info.vertex_path = std::string(buf2);
        else if (strcmp(buf, "fragment:") == 0)
            info.fragment_path = std::string(buf2);
        else if (strcmp(buf, "obj:") == 0)
            info.obj_path = std::string(buf2);
        else if (strcmp(buf, "diffuse:") == 0)
            info.diffuse_path = std::string(buf2);
        else if (strcmp(buf, "normal:") == 0)
            info.normal_path = std::string(buf2);
        else if (strcmp(buf, "specular:") == 0)
            info.specular_path = std::string(buf2);
        else if (strcmp(buf, "type:") == 0)
            info.type = atoi(buf2);
        else if (strcmp(buf, "name:") == 0)
            info.name = std::string(buf2);
        else
            log.write("  Unkown selector: %s -- skipping\n", buf);
    }

    fclose(file);
    return info;
}

GLuint EntityLoader::load_shader(const char* path, GLenum type)
{
    GLuint shader_id = glCreateShader(type);

    log.write("Loading shader: %s\n", path);

    /* Read contents of the shader files */
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        log.write("  Shader not found: %s\n", path);
        return 0;
    }

    /* Find size of the file and allocate a buffer */
    fseek(fp, 0, SEEK_END);
    size_t buf_size = ftell(fp);
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL)
    {
        log.write("  Memory error\n");
        fclose(fp);
        return 0;
    }

    /* Read file contents */
    fseek(fp, 0, SEEK_SET);
    fread(buf, 1, buf_size, fp);
    fclose(fp);

    /* Sometimes there was some garbage in the end of the file preventing
     * compilation. This way everything after the last \n} is removed */

    unsigned int i = strlen(buf)-1;
    while (i > 0)
    {
        if (buf[i] == '}')
        {
            if (buf[i-1] == '\n')
            {
                break;
            }
        }
        i--;
    }
    if (i == 0)
    {
        log.write("  Failed to load shader: %s\n", path);
        return 0;
    }
    if (i+1 < strlen(buf))
        buf[i+1] = '\0';

    /* Time to compile the shader */

    log.write("Compiling shader: %s\n", path);

    glShaderSource(shader_id, 1, &buf, NULL);
    glCompileShader(shader_id);

    /* Check shader */
    GLint result = GL_FALSE;
    int info_log_len;

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_len);
    if (info_log_len > 0)
    {
        char* logbuf = (char*)malloc(info_log_len);
        glGetShaderInfoLog(shader_id, info_log_len, NULL, logbuf);
        log.write("%s\n", logbuf);
        free(logbuf);
        free(buf);
        return 0;
    }

    free(buf);

    return shader_id;
}

bool EntityLoader::load_shaders(Object3dData *obj)
{
    GLuint vertex_shader_id = load_shader(obj->ent.vertex_path.c_str(), GL_VERTEX_SHADER);
    GLuint fragment_shader_id = load_shader(obj->ent.fragment_path.c_str(), GL_FRAGMENT_SHADER);

    if (vertex_shader_id == 0 || fragment_shader_id == 0)
        return false;

    /* Link program */
    log.write("Linking shaders for %s (ID: %d)\n", obj->ent.name.c_str(), obj->ent.type);

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    /* Check */
    GLint result = GL_FALSE;
    int info_log_len;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_len);
    if (info_log_len > 0)
    {
        char* logbuf = (char*)malloc(info_log_len);
        glGetProgramInfoLog(program_id, info_log_len, NULL, logbuf);
        log.write("%s\n", logbuf);
        free(logbuf);
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    obj->shader_id = program_id;
    return true;
}

bool EntityLoader::load_obj(Object3dData *obj)
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    std::vector<unsigned int> vertex_indices, uv_indices, norm_indices;
    std::vector<glm::vec3> tmp_vertices;
    std::vector<glm::vec2> tmp_uvs;
    std::vector<glm::vec3> tmp_norms;

    const char* path = obj->ent.obj_path.c_str();

    log.write("Loading model: %s\n", path);

    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        log.write("File not found: %s\n", path);
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
                log.write("Parsing failed: %s\n", path);
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
    fclose(fp);

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
        vertices.push_back(vertex);
        uvs.push_back(uv);
        normals.push_back(norm);
    }

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_norms;
    std::vector<glm::vec3> indexed_tangents;
    std::vector<glm::vec3> indexed_bitangents;

    computeTangentBasis(vertices, uvs, normals, tangents, bitangents);
    indexVBO_TBN(vertices, uvs, normals, tangents, bitangents, \
                 indices, indexed_vertices, indexed_uvs, indexed_norms, \
                 indexed_tangents, indexed_bitangents);

    glGenBuffers(1, &obj->vertex_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vertex_buf_id);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), \
                 &indexed_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &obj->uv_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, obj->uv_buf_id);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), \
                 &indexed_uvs[0], GL_STATIC_DRAW);

    glGenBuffers(1, &obj->normal_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, obj->normal_buf_id);
    glBufferData(GL_ARRAY_BUFFER, indexed_norms.size() * sizeof(glm::vec3), \
                 &indexed_norms[0], GL_STATIC_DRAW);

    glGenBuffers(1, &obj->tangent_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, obj->tangent_buf_id);
    glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(glm::vec3), \
                 &indexed_tangents[0], GL_STATIC_DRAW);

    glGenBuffers(1, &obj->bitangent_buf_id);
    glBindBuffer(GL_ARRAY_BUFFER, obj->bitangent_buf_id);
    glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(glm::vec3), \
                 &indexed_bitangents[0], GL_STATIC_DRAW);

    glGenBuffers(1, &obj->elem_buf_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->elem_buf_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), \
                 &indices[0], GL_STATIC_DRAW);

    obj->faces = indices.size();

    return true;
}

bool EntityLoader::load_textures(Object3dData *obj)
{
    if (obj->ent.diffuse_path != "none")
    {
        obj->diffuse_tex = SOIL_load_OGL_texture(obj->ent.diffuse_path.c_str(),
                                                 SOIL_LOAD_AUTO, \
                                                 SOIL_CREATE_NEW_ID,
                                                 /* SOIL_FLAG_MIPMAPS \
                                                 | SOIL_FLAG_INVERT_Y \
                                                 | SOIL_FLAG_NTSC_SAFE_RGB \
                                                 | SOIL_FLAG_COMPRESS_TO_DXT */
                                                 SOIL_FLAG_DDS_LOAD_DIRECT);
    }
    else
    {
        obj->diffuse_tex = 0;
        return false;
    }

    if (obj->ent.normal_path != "none")
    {
        obj->normal_tex = SOIL_load_OGL_texture(obj->ent.normal_path.c_str(),
                                                SOIL_LOAD_AUTO, \
                                                SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS \
                                                | SOIL_FLAG_INVERT_Y \
                                                | SOIL_FLAG_NTSC_SAFE_RGB \
                                                | SOIL_FLAG_COMPRESS_TO_DXT);
    }
    else
    {
        obj->normal_tex = 0;
    }

    if (obj->ent.specular_path != "none")
    {
        obj->specular_tex = SOIL_load_OGL_texture(obj->ent.specular_path.c_str(),
                                                  SOIL_LOAD_AUTO, \
                                                  SOIL_CREATE_NEW_ID, \
                                                  /* SOIL_FLAG_MIPMAPS \
                                                  | SOIL_FLAG_INVERT_Y \
                                                  | SOIL_FLAG_NTSC_SAFE_RGB \
                                                  | SOIL_FLAG_COMPRESS_TO_DXT */
                                                  SOIL_FLAG_DDS_LOAD_DIRECT);
    }
    else
    {
        obj->specular_tex = 0;
    }

    return true;
}

void EntityLoader::get_uniforms(Object3dData *obj)
{
    obj->diffuse_id = glGetUniformLocation(obj->shader_id, "diffuse_sampler");
    obj->normal_id = glGetUniformLocation(obj->shader_id, "normal_sampler");
    obj->specular_id = glGetUniformLocation(obj->shader_id, "specular_sampler");
}
