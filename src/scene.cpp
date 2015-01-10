#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "game.h"
#include "scene.h"

Scene::Scene(Logger &log)
    :log(log)
{
    // Create OpenGL context
    if (!glfwInit())
    {
        log.write("Failed to init GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, Game::settings.video.aa_samples); /* Antialiasing */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* OS X */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(Game::settings.video.width, Game::settings.video.height, "Razngin", NULL, NULL);

    if (window == NULL)
    {
        log.write("Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;

    if (glewInit() != GLEW_OK)
    {
        log.write("Failed to init GLEW\n");
        exit(EXIT_FAILURE);
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0,0,0,0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
}

Scene::~Scene()
{
    glDeleteBuffers(1, &obj->vertex_buf_id);
    glDeleteBuffers(1, &obj->uv_buf_id);
    glDeleteBuffers(1, &obj->normal_buf_id);
    glDeleteBuffers(1, &obj->tangent_buf_id);
    glDeleteBuffers(1, &obj->bitangent_buf_id);
    glDeleteBuffers(1, &obj->elem_buf_id);

    glDeleteProgram(obj->shader_id);

    glDeleteTextures(1, &obj->diffuse_tex);
    glDeleteTextures(1, &obj->normal_tex);
    glDeleteTextures(1, &obj->specular_tex);

    glDeleteVertexArrays(1, &vao_id);

    glfwTerminate();
}
