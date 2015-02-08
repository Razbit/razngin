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
#include "game.h"
#include "renderer.h"

Renderer::Renderer(Logger& log, Scene* scene)
    : log(log), scene(scene)
{
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(scene->obj->shader_id);

    int w, h;
    glfwGetWindowSize(scene->window, &w, &h);
    scene->projection = glm::perspective((float)Game::settings->get("video.fov")->n, \
                                         (float)w/h, 0.1f, 100.0f);
    scene->view = glm::lookAt(glm::vec3(4,3,-3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 model(1.0f);

    GLuint model_id = glGetUniformLocation(scene->obj->shader_id, "m");
    GLuint view_id = glGetUniformLocation(scene->obj->shader_id, "v");
    GLuint projection_id = glGetUniformLocation(scene->obj->shader_id, "p");

    glUniformMatrix4fv(model_id, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(view_id, 1, GL_FALSE, &scene->view[0][0]);
    glUniformMatrix4fv(projection_id, 1, GL_FALSE, &scene->projection[0][0]);


    GLuint light_pos_id = glGetUniformLocation(scene->obj->shader_id, "light_position_worldspace");
    GLuint light_power_id = glGetUniformLocation(scene->obj->shader_id, "light_power");
    GLuint light_color_id = glGetUniformLocation(scene->obj->shader_id, "light_color");

    glm::vec3 light_pos(4, 4, 4);
    glm::vec3 light_color(1, 1, 1);
    GLfloat light_power = 100.0f;

    glUniform3f(light_pos_id, light_pos.x, light_pos.y, light_pos.z);
    glUniform3f(light_color_id, light_color.x, light_color.y, light_color.z);
    glUniform1f(light_power_id, light_power);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->obj->diffuse_tex);
    glUniform1i(scene->obj->diffuse_id, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, scene->obj->normal_tex);
    glUniform1i(scene->obj->normal_id, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, scene->obj->specular_tex);
    glUniform1i(scene->obj->specular_id, 2);

    /* 1st attrib. buffer: vertices */
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, scene->obj->vertex_buf_id);
    glVertexAttribPointer(
                0,          /* Buffer # */
                3,          /* size */
                GL_FLOAT,   /* type */
                GL_FALSE,   /* normalized */
                0,          /* stride */
                (void*) 0   /* offset */
                );

    /* 2nd attribute buffer: uvs */
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, scene->obj->uv_buf_id);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, scene->obj->normal_buf_id);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, scene->obj->tangent_buf_id);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(4);
    glBindBuffer(GL_ARRAY_BUFFER, scene->obj->bitangent_buf_id);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    /* Index buffer */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene->obj->elem_buf_id);

    /* Draw */
    glDrawElements(GL_TRIANGLES, scene->obj->faces, GL_UNSIGNED_SHORT, (void*)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);

    scene->time = glfwGetTime();

    glfwSwapBuffers(scene->window);
}
