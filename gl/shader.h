#ifndef SHADER_H
#define SHADER_H
#include <stdbool.h>
enum ShaderType
{
	CRPG_SHADER_VERTEX = 0,
	CRPG_SHADER_FRAGMENT,
	CRPG_SHADER_GEOMETRY,
	CRPG_SHADER_COMPUTE,
	CRPG_SHADER_TESSCONTROL,
	CRPG_SHADER_TESSEVAL,
	CRPG_SHADER_LAST
};

typedef struct {} Shader;

Shader *crpgShaderNew(const char *shaderName);
void crpgShaderUse(Shader *s);
void crpgShaderSetBool(Shader *s, const char *name, bool val);
void crpgShaderSetInt(Shader *s, const char *name, int val);
void crpgShaderSetFloat(Shader *s, const char *name, float val);
void crpgShaderFree(Shader *s);
#endif//SHADER_H
