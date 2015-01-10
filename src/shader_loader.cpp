#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include <shader_loader.h>

extern FILE* logfp;
extern FILE* errlog;

/* I know, the file input could have been done in C++ way, but since OGL wants
 * C-strings instead of std::string, I think this is more efficent */

static GLuint load_shader(const char* path, GLenum type);

GLuint load_shaders(const char* vertex_path, const char* fragment_path)
{
    GLuint vertex_shader_id = load_shader(vertex_path, GL_VERTEX_SHADER);
    GLuint fragment_shader_id = load_shader(fragment_path, GL_FRAGMENT_SHADER);

    /* Link program */

    fprintf(logfp, "Linking shaders\n");

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    /* Check */
    GLint result = GL_FALSE;
    int info_log_len;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_len);
    if (info_log_len > 0)
    {
        char* log = (char*)malloc(info_log_len);
        glGetProgramInfoLog(program_id, info_log_len, NULL, log);
        fprintf(logfp, "%s\n", log);
        free(log);
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;

}

static GLuint load_shader(const char *path, GLenum type)
{
    GLuint shader_id = glCreateShader(type);

    fprintf(logfp, "Loading shader: %s\n", path);

    /* Read contents of the shader files */
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        fprintf(errlog, "Shader not found: %s\n", path);
        exit(EXIT_FAILURE);
    }

    /* Find size of the file and allocate a buffer */
    fseek(fp, 0, SEEK_END);
    size_t buf_size = ftell(fp);
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL)
    {
        fprintf(errlog, "Memory error\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    /* Read file contents */
    fseek(fp, 0, SEEK_SET);
    fread(buf, 1, buf_size, fp);
    fclose(fp);

    /* Sometimes there was some garbage in the end of the file preventing
     * compilation. This way everything after the last \n} is removed */

    int i = strlen(buf)-1;
    while (i > 0)
    {
        if (buf[i] == '}')
        {
            if (buf[i-1] == '\n')
            {
                break;
            }
        }
        i--;
    }
    if (i == 0)
    {
        fprintf(errlog, "Failed to load shader: %s\n", path);
        exit(EXIT_FAILURE);
    }
    if (i+1 < strlen(buf))
        buf[i+1] = '\0';

    /* Time to compile the shader */

    fprintf(logfp, "Compiling shader: %s\n", path);

    glShaderSource(shader_id, 1, &buf, NULL);
    glCompileShader(shader_id);

    /* Check shader */
    GLint result = GL_FALSE;
    int info_log_len;

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_len);
    if (info_log_len > 0)
    {
        char* log = (char*)malloc(info_log_len);
        glGetShaderInfoLog(shader_id, info_log_len, NULL, log);
        fprintf(errlog, "%s\n", log);
        free(log);
        free(buf);
        exit(EXIT_FAILURE);
    }

    free(buf);

    return shader_id;
}
