#ifndef SETTINGS_H
#define SETTINGS_H

#include <string.h>
/**
 * @file
 * @brief Settings of the game.
 */

/**
 * @brief A struct for storing video settings
 */
struct s_video
{
    /** Width of the scene */
    int width;
    /** Height of the scene */
    int height;
    /** Field of View */
    float fov;
    /** Aspect ratio */
    float aspect;
    /** Anti-aliasing samples */
    int aa_samples;
};

/**
 * @brief A struct for storing game settings
 */
struct s_settings
{
    /** Video settings @sa s_video */
    struct s_video video;
};

class Setting
{
public:
    Setting(const char* _name) : next(NULL)
    {
        name = (char*)malloc(strlen(_name) + 1);
        strcpy(name, _name);
    }

    char* name;
    Setting* next;
};

class Section
{
public:
    Section(const char* _section) : settings(NULL)
    {
        section = (char*)malloc(strlen(_section) + 1);
        strcpy(section, _section);
    }

    ~Section()
    {

        free(section);
    }

    void add(Setting* setting)
    {
        Setting* ptr = settings;

        while (ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = setting;
    }

    Setting* get(const char* name)
    {
        Setting* ptr = settings;
        while (true)
        {
            if (ptr = NULL)
                return NULL;
            if (strcmp(name, ptr->name))
        }
    }

    char* section;
    Setting* settings;

};

#endif // SETTINGS_H
