#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "utils/logger.h"
#include "game.h"

#include "settingsloader.h"

bool SettingsLoader::load_file(const char* path)
{
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        log.write("Configuration file not found: %s\n", path);
        return false;
    }

    while (fgets(buf, 1024, fp) != NULL)
    {
        char buf[1024];
        char key[32];
        char* ptr;

        char* p = strrchr(buf, '\n');
        if (p != NULL)
            p = NULL;

        while (isspace(*buf))
            buf++;

        if (*buf == '#')
            continue;

        if (*buf == '[') // The line contains a section (e.g. [video])
        {
            char[32] sect;
            int i = 0;
            while (*buf != ']')
                sect[i++] = *buf++;
            sect[i] == 0;

            set_section(sect);

            continue;
        }

        for (int i = 0; i < 32; i++)
        {
            if (buf[i] == ':')
            {
                key[i++] = 0;

                while (isspace(buf[i]))
                    i++;

                ptr = &buf[i]; // ptr points to the beginning of the value
                break;
            }
            key[i] = buf[i];
        }

        set_value(key, ptr);

    }
}

static char* strtolower(char* str)
{
    int i = 0;
    while (str[i] != NULL)
    {
        str[i] = tolower(str[i]);
        i++;
    }

    return str;
}

void SettingsLoader::set_section(const char *sect)
{
    if (strcmp(strtolower(section), "video") == 0)
        section = SEC_VIDEO;
    //todo: other sections
}

void SettingsLoader::set_value(const char *key, const char *val)
{

}
