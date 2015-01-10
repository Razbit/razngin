#ifndef ENTITYLOADER_H
#define ENTITYLOADER_H

#include <string>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "utils/logger.h"
#include "object3d.h"

class EntityLoader
{
public:
    EntityLoader(Logger &log):log(log) {}

    struct entity_info parse_file(const char* path);
    bool load_shaders(Object3dData* obj);
    bool load_obj(Object3dData* obj);
    bool load_textures(Object3dData* obj);
    void get_uniforms(Object3dData* obj);

private:
    GLuint load_shader(const char* path, GLenum type);
    Logger& log;
};

#endif // ENTITYLOADER_H
