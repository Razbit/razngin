/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

/* Block defines a block in the world, one instance per block */

#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <soil/SOIL.h>
#include <string>

#include "object3d.h"
#include "entityinfo.h"
#include "utils/logger.h"

class Block
{
public:
    Block(Logger &log)
        :log(log)
    {}
    virtual ~Block(){}

    struct Object3dData* obj;

    Logger& log;
    int id;

    GLuint model_matrix_id;
};

#endif // BLOCK_H
