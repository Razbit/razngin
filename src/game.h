#ifndef GAME_H
#define GAME_H

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
    static s_settings settings;
};

#endif // GAME_H
