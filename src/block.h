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

/**
 * @file
 * @brief A class describing a block in the world.
 */

/**
  * @brief Defines a block in the world.
  * @details So far, only contains the data needed by OpenGL. One intance/block in the world.
  * @author Eetu "Razbit" Pesonen
  * @version 0.01
  * @date 2015
  * @copyright Any kind of redistribution without explicit permission is prohibited.
  */
class Block
{
public:
    /**
     * @brief Sets up logging, places the block in the world.
     * @param log The logger using which log messages are delivered.
     */
    Block(Logger &log)
        :log(log)
    {}
    virtual ~Block(){}

    /** A pointer to Object3dData matching the type of the block. */
    struct Object3dData* obj;

    /** A reference of the logger we are using */
    Logger& log;
    /** A unique ID for the block */
    int id;

    /** The ID of the model matrix. */
    GLuint model_matrix_id;
};

#endif // BLOCK_H
