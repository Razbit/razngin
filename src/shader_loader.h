#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint load_shaders(const char *vertex_path, const char *fragment_path);

#endif // SHADER_LOADER_H
