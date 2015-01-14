#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#include <string>

/**
 * @file
 * @brief Data structure for holding information extracted from model preferences.
 */

/**
 * @brief Holds information extracted from the model preferences file durign loading.
 * @author Eetu "Razbit" Pesonen
 * @version 0.01
 * @date 2015
 * @copyright Any kind of redistribution without explicit permission is prohibited.
 */
struct entity_info
{
    /** Path to the vertex shader */
    std::string vertex_path;

    /** Path to the fragment shader */
    std::string fragment_path;

    /** Path to the .obj file */
    std::string obj_path;

    /** Path to the diffuse texture */
    std::string diffuse_path;

    /** Path to the normal map */
    std::string normal_path;

    /** Path to the specular texture */
    std::string specular_path;

    /** Type-id of the object */
    int type;

    /** "Name" of the object */
    std::string name;
};

#endif // ENTITYINFO_H
