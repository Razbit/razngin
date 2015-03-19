#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

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
#include "rvec.h"

class InputSystem
{
public:
    InputSystem();
    ~InputSystem();
};

#endif // INPUTSYSTEM_H
