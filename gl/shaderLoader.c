#include "shaderLoader.h"
#include "fileRead.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "err.h"

static char *fileEnds[] = {
	".vert",
	".frag",
	".comp",
	".tesc",
	".tese"
};
static char *dirPath = "gl/shaders/";

char *shader_load_src(const char *name, enum ShaderType type)
{
	GLchar *src = NULL;

	int nSize = strlen(name);
	int eSize = strlen(fileEnds[type]);
	int dSize = strlen(dirPath);

	int tSize = dSize + (2*nSize) + eSize + 2;

	// constructing the final path string
	char *path = malloc(tSize);
	printf("sizes: dSize=%d nSize=%d, eSize=%d\n", dSize, nSize, eSize);
	printf("total allocated %d\n", tSize);

	strcpy(path, dirPath);
	strcat(path, name);
	strcat(path, "/");
	strcat(path, name);
	strcat(path, fileEnds[type]);

	// debug output
	printf("path length is %ld\n", strlen(path));
	printf("loading shader from file '%s'\n\n", path);
	src = readFile(path);
	free(path);
	return src;
}

void shader_compile(unsigned int shader, const GLchar *shaderSrc, const char *description)
{
	int success;
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
}

void shader_free_src(GLchar *src)
{
	free(src);
}
