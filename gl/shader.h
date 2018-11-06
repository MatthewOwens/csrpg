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

typedef struct {} crpgShader;

crpgShader *crpgShaderNew(const char *shaderName);
void crpgShaderUse(crpgShader *s);
void crpgShaderSetBool(crpgShader *s, const char *name, bool val);
void crpgShaderSetInt(crpgShader *s, const char *name, int val);
void crpgShaderSetFloat(crpgShader *s, const char *name, float val);
void crpgShaderFree(crpgShader *s);
unsigned int crpgShaderID(crpgShader *s);
#endif//SHADER_H
