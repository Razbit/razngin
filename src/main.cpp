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

#include "utils/platform.h"

#ifdef PLATFORM_WIN32
    #include <windows.h> //FreeConsole()
    #include <direct.h> //getcwd()
#else
    #include <unistd.h>
#endif

#include "scene.h"
#include "game.h"
#include "renderer.h"
#include "object3d.h"
#include "entityloader.h"
#include "utils/loggerconsole.h"
#include "utils/loggerfile.h"
#include "settingsloader.h"

//#define NOCONSOLE

int main()
{
#ifdef NOCONSOLE
    LoggerFile logger("logfile.log");
#ifdef PLATFORM_WIN32
    FreeConsole();
#endif
#else
    LoggerConsole logger;
#endif

    SettingsLoader settingsldr(logger);
    Game::settings = settingsldr.load("resource/settings.ini");

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
    } while(glfwWindowShouldClose(scene->window) == 0);

    delete scene;
    delete rend;
    delete obj;
    delete Game::settings;

    return 0;
}
