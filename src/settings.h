#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <string.h>
#include <stdio.h>

/**
 * @file
 * @brief Settings of the game.
 */

/**
 * @brief value of an entry in the settings list
 */
union s_val
{
    int n;
    float f;
    char str[1024];
};

/**
 * @brief An entry in the settings list
 */
class Setting
{
public:
    Setting(std::string key, int n) : key(key), next(NULL) {val.n = n;}
    Setting(std::string key, double f) : key(key), next(NULL) {val.f = f;}
    Setting(std::string key, char* str) : key(key), next(NULL)
    {
        strncpy(val.str, str, 1024);
    }

    ~Setting(){}


    /**
     * @brief Name of the entry
     */
    std::string key;
    /**
     * @brief Value of the entry
     */
    s_val val;

    /**
     * @brief A pointer to the next entry in the list
     */
    Setting* next;
};

/**
 * @brief Contains a list of settings of a section
 */
class SettingGroup
{
public:
    SettingGroup(std::string name): name(name), list(NULL), next(NULL){}
    ~SettingGroup()
    {
        Setting* ptr1 = list;
        Setting* ptr2 = NULL;
        while (ptr1 != NULL)
        {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            delete ptr2;
        }
    }

    /**
     * @brief Add a new entry to the settings group
     * @param setting Setting to be added
     */
    void add(Setting* setting)
    {
        if (list == NULL)
        {
            list = setting;
        }
        else
        {
            Setting* ptr = list;
            while(ptr->next != NULL)
                ptr = ptr->next;

            ptr->next = setting;
        }
    }

    s_val* get(std::string key)
    {
        Setting* ptr = list;
        while(ptr->key != key)
        {
            ptr = ptr->next;
            if (ptr == NULL) // We have reached the end, thus we return 0
            {
                return NULL;
            }
        }

        return &(ptr->val);
    }

    /** Name of the group */
    std::string name;
    /** Pointer to the beginning of the list */
    Setting* list;
    /** Pointer to the nextx element in the list */
    SettingGroup* next;
};

/**
 * @brief Contains game settings and handlers for getting/setting them
 */
class Settings
{
public:
    Settings() : list(NULL), cur(NULL) {}

    ~Settings()
    {
        SettingGroup* ptr1 = list;
        SettingGroup* ptr2 = NULL;
        while (ptr1 != NULL)
        {
            ptr2 = ptr1;
            ptr1 = ptr1->next;
            delete ptr2;
        }
    }

    /**
     * @brief Add a new settings group
     * @param group Group to add
     */
    void addGroup(std::string group)
    {
        SettingGroup* ptr;
        if (list == NULL)
        {
           list = new SettingGroup(group);
           cur = list;
        }
        else
        {
            ptr = list;
            while (ptr->next != NULL)
                ptr = ptr->next;
           ptr->next = new SettingGroup(group);
           cur = ptr->next;
        }
    }

    /**
     * @brief Find group from the list
     * @param name Name of the group to be looked for
     * @return A pointer to the group with the name <name>, NULL if not found
     */
    SettingGroup* getGroup(std::string name)
    {
        SettingGroup* ret = list;
        while (ret != NULL && ret->name != name)
            ret = ret->next;
        return ret;
    }

    void add(Setting* setting)
    {
        cur->add(setting);
    }

    /**
     * @brief Find a setting -entry using "group.setting" key
     * @param query What setting we want, "group.setting"
     * @return An instance of s_val union containing the data
     */
    s_val* get(std::string query)
    {
        char* group = new char[64];
        char* key = new char[64];

        group = strtok((char*)query.c_str(), ".");
        key = strtok(NULL, "");

        SettingGroup* ptr = getGroup(group);
        return ptr->get(key);
    }

    /** Beginning of the list */
    SettingGroup* list;
    /** Current group/section */
    SettingGroup* cur;
};



#endif // SETTINGS_H
