#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

/**
 * @file
 * @brief Loads and parses the settings file
 */

#include "utils/logger.h"
#include "game.h"

enum eSections
{
    SEC_VIDEO
};

/**
 * @brief Loads settings.
 * @details Settings are loaded from .conf and stored to Game::settings.
 * @author Eetu "Razbit" Pesonen
 * @version 0.01
 * @date 2015
 * @copyright Any kind of redistribution without explicit permission is prohibited.
 */
class SettingsLoader
{
public:
    SettingsLoader(Logger &log) : log(log) {}

    bool load_file(const char* path);

private:
    void set_section(const char* sect);
    void set_value(const char* key, const char* val);

    eSection section;

    Logger& log;

};

#endif // SETTINGSLOADER_H
