#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "utils/logger.h"

#include "settingsloader.h"
#include "game.h"
#include "settings.h"

SettingsLoader::SettingsLoader()
{
    log = Game::log;
}

SettingsLoader::~SettingsLoader()
{

}

Settings* SettingsLoader::load(const char* path)
{
    log->write("Loading settings from '%s'\n", path);

    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        log->error(SEVERE, "Loading settings failed: No such file: %s\n", path);
    }

    Settings* ret = new Settings;

    /* We use the ini-file like syntax:
     * [section]
     * key=val
     * # comment
     */

    while (1)
    {
        char buf[1500];
        char key[64];
        char val[1024];

        memset(buf, 0, 1500);
        memset(key, 0, 64);
        memset(val, 0, 1024);

        if (fgets(buf, 1500, file) == NULL)
            break;

        if (buf[0] == '#') // comment
        {
            continue;
        }

        else if (buf[0] == '[') // probably a section/group header
        {
            char tmp[100];
            int i = 1;
            for (; i < 80; i++)
                if (buf[i] == ']')
                    break;
            i--;
            strncpy(tmp, &buf[1], i);
            tmp[i] = '\0';

            ret->addGroup(tmp);

            log->write("Loading section '%s'\n", tmp);
        }

        else
        {
            Setting* setting = NULL;

            int j = 0;
            for (; j < 64; j++)
            {
                if (buf[j] != '=')
                    key[j] = buf[j];
                else
                    break;
            }
            // todo: equals sign not reached

            j++;
            for (int k = 0; k < 1024; j++, k++)
            {
                if (buf[j] != '\0')
                    val[k] = buf[j];
                else
                {
                    val[k] = '\0';
                    break;
                }
            }

            // A string value
            if (val[0] == '"')
            {
                char tmp[1024];
                int i = 1;
                for (; i < 1024; i++)
                    if (val[i] == '"')
                        break;
                i--;
                strncpy(tmp, &val[1], i);
                tmp[i] = '\0';

                setting = new Setting(key, tmp);

                log->write("Loading <%s, %s>\n", setting->key.c_str(), setting->val.str);
            }

            // Numeric value
            if (isdigit(val[0]))
            {
                // Float
                if (strchr(&val[0], '.') != NULL)
                {
                    setting = new Setting(key, atof(val));
                    log->write("Loading <%s, %f>\n", setting->key.c_str(), setting->val.f);
                }
                else
                {
                    setting = new Setting(key, atoi(val));
                    log->write("Loading <%s, %d>\n", setting->key.c_str(), setting->val.n);
                }

            }

            ret->cur->add(setting);

        }

    }

    log->write("Done loading settings\n");
    fclose(file);
    return ret;
}

