#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "utils/logger.h"
#include "object3d.h"

/**
 * @file
 * @brief Info and state of the renderable scene.
 */

/**
  * @brief Holds info and state of the renderable scene.
  * @details Contains the view and projection matrices, light information, window pointer and time
  * of last render.
  * @author Eetu "Razbit" Pesonen
  * @version 0.01
  * @date 2015
  * @copyright Any kind of redistribution without explicit permission is prohibited.
  */
class Scene
{
public:
    /**
     * @brief Sets up logging and creates OpenGL context.
     * @param log The logger using which log messages are delivered.
     */
    Scene(Logger &log);
    /**
     * @brief Cleans up the OpenGL -related data.
     */
    virtual ~Scene();

    /** A pointer to the window in which we are drawing */
    GLFWwindow* window;

    /** Vertex Array Object */
    GLuint vao_id;

    /** Projection matrix. */
    glm::mat4 projection;
    /** View matrix. */
    glm::mat4 view;

    /** Position of the (main) light in the world */
    glm::vec3 light_pos;
    /** Color of the (main) light */
    glm::vec3 light_color;
    /** Power of the (main) light */
    GLfloat light_power;

    /// @cond TEST
    void setObj(Object3dData* _obj)
    {
        obj = _obj;
    }

    Object3dData* obj;
    /// @endcond

    /** %Time of previous update */
    double time;

private:
    /**
     * @brief  A reference to the Logger that is in use.
     */
    Logger& log;
};

#endif // SCENE_H
