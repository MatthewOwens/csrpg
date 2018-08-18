#ifndef SHADER_LOADER
#define SHADER_LOADER
#include <GL/glew.h>

enum ShaderType
{
	VERTEX = 0,
	FRAGMENT,
	GEOMETRY,
	COMPUTE,
	TESSCONTROL,
	TESSEVAL
};

char *shader_load_src(const char *name, enum ShaderType type);
void shader_compile(unsigned int shader, const GLchar *shaderSrc, const char *description);
void shader_free_src(GLchar *src);
#endif//SHADER_LOADER
