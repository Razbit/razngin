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
#include "object3d.h"

class Renderer
{
public:
    Renderer(Logger& log, Scene* scene);

    void render();

    Scene* scene;
    Logger& log;
};

#endif // RENDERER_H
