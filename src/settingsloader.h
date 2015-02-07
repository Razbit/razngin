#ifndef SETTINGSLOADER_H
#define SETTINGSLOADER_H

#include "settings.h"
#include "utils/logger.h"

class SettingsLoader
{
public:
    SettingsLoader(Logger& log);
    ~SettingsLoader();

    Settings* load(const char* path);

private:
    /** The logger to be used */
    Logger& log;
};

#endif // SETTINGSLOADER_H
