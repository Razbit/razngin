#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

#include "settings.h"
#include "utils/logger.h"
/**
  * @file
  * @brief A class for loading settings
  */

/**
 * @brief Loads settings from the ini file
 */
class SettingsLoader
{
public:
    SettingsLoader();
    ~SettingsLoader();

    /** Load a file */
    Settings* load(const char* path);

private:
    /** The logger to be used */
    Logger* log;
};

#endif // SETTINGSLOADER_H
