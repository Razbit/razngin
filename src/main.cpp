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
    Game::log = new LoggerFile("logfile.log");
#ifdef PLATFORM_WIN32
    FreeConsole();
#else
    //TODO: No console in Linux?
#endif
#else
    Game::log = new LoggerConsole();
#endif

    Game::settingsldr = new SettingsLoader();
    Game::settings = Game::settingsldr->load("resource/settings.ini");

    Game::scene = new Scene();
    Game::renderer = new Renderer(Game::scene);
    Game::entldr = new EntityLoader();

    Object3dData* obj = new Object3dData;

    obj->ent = Game::entldr->parse_file("resource/test.model");
    Game::entldr->load_shaders(obj);
    Game::entldr->load_obj(obj);
    Game::entldr->load_textures(obj);
    Game::entldr->get_uniforms(obj);
    Game::scene->setObj(obj);

    do
    {
        Game::renderer->render();
        glfwPollEvents();
    } while(glfwGetKey(Game::scene->window, GLFW_KEY_ESCAPE) != GLFW_PRESS \
        && glfwWindowShouldClose(Game::scene->window) == 0);

    delete obj;

    Game::terminate(EXIT_SUCCESS);

    return 0;
}
