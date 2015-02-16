#ifndef ENTITYLOADER_H
#define ENTITYLOADER_H

#include <string>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "utils/logger.h"
#include "object3d.h"

/**
 * @file
 * @brief A class for loading 3D entities.
 */

/**
  * @brief Loads (3D) entities to memory.
  * @details Loads model, shaders, textures and other data from files specified in *.model
  * @author Eetu "Razbit" Pesonen
  * @version 0.01
  * @date 2015
  * @copyright Any kind of redistribution without explicit permission is prohibited.
  */

class EntityLoader
{
public:
    /**
     * @brief Constructor
     */
    EntityLoader();

    /**
     * @brief Parse the .model file.
     * @param path The path to the .model file.
     * @return entity_info containing all the information needed by the coming loaders.
     */
    struct entity_info parse_file(const char* path);

    /**
     * @brief Load the vertex and fragment shader from files specified in the entity_info.
     * @param obj Pointer to struct Object3dData containing relevant information on the object.
     * @return True on success, false otherwise.
     */
    bool load_shaders(Object3dData* obj);

    /**
     * @brief Loadsthe .obj file specified in the entity_info.
     * @param obj Pointer to struct Object3dData containing relevant information on the object.
     * @return True on success, false otherwise.
     */
    bool load_obj(Object3dData* obj);

    /**
     * @brief Load textures specified in entity_info.
     * @param obj Pointer to struct Object3dData containing relevant information on the object.
     * @return True on success, false otherwise.
     */
    bool load_textures(Object3dData* obj);

    /**
     * @brief Set OpenGL shader handlers for the textures.
     * @param obj Pointer to struct Object3dData containing relevant information on the object.
     */
    void get_uniforms(Object3dData* obj);

private:
    /**
     * @brief Load one shader.
     * @param path C-String containing path to the shader file.
     * @param type OpenGL-enumerated type telling what shader we are loading (vertex or fragment).
     * @return
     */
    GLuint load_shader(const char* path, GLenum type);

    /**
     * @brief  A reference to the Logger that is in use.
     */
    Logger* log;
};

#endif // ENTITYLOADER_H
