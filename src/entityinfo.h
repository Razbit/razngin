/* Copyright Eetu "Razbit" Pesonen, 2015
 * Any kind of redistribution without explicit permission is prohibited. */

#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#include <string>

// Holds information extracted from the model preferences file durign loading
struct entity_info
{
    std::string vertex_path;
    std::string fragment_path;
    std::string obj_path;
    std::string diffuse_path;
    std::string normal_path;
    std::string specular_path;

    int type;
    std::string name;
};

#endif // ENTITYINFO_H
