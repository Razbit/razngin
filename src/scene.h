/* Holds state of the scene */

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

class Scene
{
public:
    Scene(Logger &log);
    virtual ~Scene();

    GLFWwindow* window;

    GLuint vao_id;

    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 light_pos;
    glm::vec3 light_color;
    GLfloat light_power;

    void setObj(Object3dData* _obj)
    {
        obj = _obj;
    }

    Object3dData* obj;

    double time;

private:
    Logger& log;
};

#endif // SCENE_H
