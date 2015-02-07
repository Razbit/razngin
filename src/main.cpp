/**
  * @brief For now, the initialization things are done here.
  * @author Eetu "Razbit" Pesonen
  * @version 0.01
  * @date 2015
  * @copyright Any kind of redistribution without explicit permission is prohibited.
  *
  */

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.h"
#include "game.h"
#include "renderer.h"
#include "object3d.h"
#include "entityloader.h"
#include "utils/loggerconsole.h"
#include "utils/loggerfile.h"
#include "settingsloader.h"


int main()
{
    Game::settings.video.aa_samples = 4;
    Game::settings.video.fov = 75;
    Game::settings.video.width = 1024;
    Game::settings.video.height = 768;
    Game::settings.video.aspect = (float)Game::settings.video.width/Game::settings.video.height;

    //LoggerFile logger("logfile.log");
    LoggerConsole logger;

    SettingsLoader settingsldr(logger);
    settingsldr.load("resource/settings.ini");

    Scene* scene = new Scene(logger);
    Renderer* rend = new Renderer(logger, scene);
    EntityLoader entldr(logger);


    Object3dData* obj = new Object3dData;

    obj->ent = entldr.parse_file("resource/test.model");
    entldr.load_shaders(obj);
    entldr.load_obj(obj);
    entldr.load_textures(obj);
    entldr.get_uniforms(obj);
    scene->setObj(obj);

    do
    {
        rend->render();
        glfwPollEvents();
    } while(glfwGetKey(scene->window, GLFW_KEY_ESCAPE) != GLFW_PRESS \
        && glfwWindowShouldClose(scene->window) == 0);

    delete scene;
    delete rend;
    delete obj;

    return 0;
}
