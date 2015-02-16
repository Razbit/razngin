#ifndef RENDERER_H
#define RENDERER_H

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
#include "scene.h"
#include "game.h"
#include "object3d.h"

/**
 * @file
 * @brief Scene-rendering related functionality.
 */

/**
  * @brief Renders the scene.
  * @details Renders the attached instance of Scene.
  * @author Eetu "Razbit" Pesonen
  * @version 0.01
  * @date 2015
  * @copyright Any kind of redistribution without explicit permission is prohibited.
  */
class Renderer
{
public:
    /**
     * @brief Attach the renderer to a scene, set up logging.
     * @param scene The scene we are rendering.
     */
    Renderer(Scene* scene);

    /** Render the scene */
    void render();

protected:
    /** The Logger that we are using. */
    Logger* log;
    /** A pointer to the Scene we are rendering. */
    Scene* scene;    
};

#endif // RENDERER_H
