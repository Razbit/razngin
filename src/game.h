#ifndef GAME_H
#define GAME_H

#include "utils/logger.h"
#include "renderer.h"
#include "object3d.h"
#include "settingsloader.h"
#include "entityloader.h"
#include "scene.h"
#include "renderer.h"
#include "settings.h"

/**
 * @file
 * @brief Class describing the game state and settings related functionality.
 */

/**
  * @brief %Game state and settings.
  * @author Eetu "Razbit" Pesonen
  * @version 0.01
  * @date 2015
  * @copyright Any kind of redistribution without explicit permission is prohibited.
  */
class Game
{
public:
    Game(){}

    /** Game settings */
    static Settings* settings;

    /** Logger */
    static Logger* log;

    /** Settings loader */
    static SettingsLoader* settingsldr;

    /** Entity loader */
    static EntityLoader* entldr;

    /** Scene */
    static Scene* scene;

    /** Renderer */
    static Renderer* renderer;

    /**
     * @brief Terminates the game by destructing all the key parts of the game
     */
    static void terminate(int status)
    {
        delete settings;
        delete settingsldr;
        delete entldr;
        delete scene;
        delete renderer;
        delete log;

        exit(status);
    }
};

#endif // GAME_H
