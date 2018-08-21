#include "shader.h"
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fileRead.h"
#include "err.h"
typedef struct {
	int id;
} Shader_t;

static char *fileEnds[] = {
	".vert",
	".frag",
	".comp",
	".tesc",
	".tese"
};

static char *dirPath = "shaders/";

char *shaderLoadSrc(const char *name, enum ShaderType type)
{
	GLchar *src = NULL;

	int nSize = strlen(name);
	int eSize = strlen(fileEnds[type]);
	int dSize = strlen(dirPath);

	int tSize = dSize + (2*nSize) + eSize + 2;

	// constructing the final path string
	char *path = malloc(tSize);

	strcpy(path, dirPath);
	strcat(path, name);
	strcat(path, "/");
	strcat(path, name);
	strcat(path, fileEnds[type]);

	src = readFile(path);
	free(path);
	return src;
}

int shaderCompile(unsigned int shader, const GLchar *shaderSrc, const char *description)
{
	int success = GL_FALSE;
	char log[512];
	char out[512];

	strcpy(out, "failed to compile shader: ");
	strcat(out, description);

	if(shaderSrc){
		glShaderSource(shader, 1, &shaderSrc, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if(!success){
			glGetShaderInfoLog(shader, 512, NULL, log);
			strcat(out, "!\n");
			strcat(out, log);
			err_output(out);
		}
	} else {
		strcat(out, " source is NULL!\n");
		err_output(out);
	}

	return success;
}

int getGlMacro(enum ShaderType st){
	switch(st){
		case CRPG_SHADER_VERTEX:
			return GL_VERTEX_SHADER;
		case CRPG_SHADER_FRAGMENT:
			return GL_FRAGMENT_SHADER;
		case CRPG_SHADER_GEOMETRY:
			return GL_GEOMETRY_SHADER;
		case CRPG_SHADER_COMPUTE:
			return GL_COMPUTE_SHADER;
		case CRPG_SHADER_TESSCONTROL:
			return GL_TESS_CONTROL_SHADER;
		case CRPG_SHADER_TESSEVAL:
			return GL_TESS_EVALUATION_SHADER;
	}

	return 0;
}

crpgShader *crpgShaderNew(const char *shaderName){
	Shader_t *s = malloc(sizeof(Shader_t));
	GLchar *src;
	unsigned int shader;
	char desc[128];

	s->id = glCreateProgram();

	for(int i = 0; i < CRPG_SHADER_LAST; ++i){
		src = shaderLoadSrc(shaderName, i);
		if(src){
			shader = glCreateShader(getGlMacro(i));
			// constructing a descriptive string for the compiling source
			strcpy(desc, shaderName);
			strcat(desc, fileEnds[i]);

			if(shaderCompile(shader, src, desc)){
				glAttachShader(s->id, shader);

				// Shader has been attached, so we can delete it
				glDeleteShader(shader);
				free(src);
			}
		}
	}

	glLinkProgram(s->id);
	return (crpgShader *)s;
}

void crpgShaderFree(crpgShader *s)
{
	Shader_t *st = (Shader_t *)s;
	glDeleteProgram(st->id);
}

void crpgShaderUse(crpgShader *s)
{
	Shader_t *st = (Shader_t *)s;
	glUseProgram(st->id);
}

void crpgShaderSetBool(crpgShader *s, const char *name, bool val)
{
	Shader_t *st = (Shader_t *)s;
	glUniform1i(glGetUniformLocation(st->id, name), (int)val);
}
void crpgShaderSetInt(crpgShader *s, const char *name, int val)
{
	Shader_t *st = (Shader_t *)s;
	glUniform1i(glGetUniformLocation(st->id, name), val);
}
void crpgShaderSetFloat(crpgShader *s, const char *name, float val)
{
	Shader_t *st = (Shader_t *)s;
	glUniform1f(glGetUniformLocation(st->id, name), val);
}
