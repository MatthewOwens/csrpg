#include "cube.h"
#include <stdlib.h>
#include "shader.h"
#include "texture.h"
#include <GL/glew.h>
#include <stb/stb_image.h>
#include "err.h"

static GLfloat vertices[] = {
	//X     Y     Z      U     V
	// bottom
	-1.0f,-1.0f,-1.0f,  0.0f, 0.0f,
	 1.0f,-1.0f,-1.0f,  1.0f, 0.0f,
	-1.0f,-1.0f, 1.0f,  0.0f, 1.0f,
	 1.0f,-1.0f,-1.0f,  1.0f, 0.0f,
	 1.0f,-1.0f, 1.0f,  1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,  0.0f, 1.0f,

	// top
	-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
	 1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

	// front
	-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
	 1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
	 1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

	// back
	-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
	-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
	 1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	 1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
	 1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

	// left
	-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
	-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
	-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,

	// right
	1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
	1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,   0.0f, 1.0f
};

static bool initilised = false;
static unsigned int vbo, vao, transformLoc, cameraLoc;
static crpgShader *shader = NULL;
static crpgTexture *tex = NULL;

typedef struct {
	mat4_t transform, translation, rotation, scale;
}Cube_t;

void initVertices()
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);	// unbinding vao
}

void initShader(Cube_t *ct)
{
	// loading the textures
	stbi_set_flip_vertically_on_load(true);
	tex = crpgTextureNew("textures/container.jpg");
	shader = crpgShaderNew("crate");

	crpgShaderUse(shader);
	crpgShaderSetInt(shader, "texture0", 0);
	transformLoc = glGetUniformLocation(crpgShaderID(shader), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &ct->transform);
}

void crpgCubeSetCamera(crpgCube *c, mat4_t *cam)
{
	if(cam == NULL){
		err_output("Camera is NULL!");
	}
	Cube_t *ct = (Cube_t *) c;
	crpgShaderUse(shader);
	unsigned int loc = glGetUniformLocation(crpgShaderID(shader), "camera");
	glUniformMatrix4fv(loc, 1, GL_FALSE, cam);
	crpgShaderUse(0);
}

static int printed = 0;
void crpgCubeRender(crpgCube *c)
{
	crpgShaderUse(shader);

	Cube_t *ct = (Cube_t *)c;
	ct->transform = ct->translation;
	ct->transform = m4_mul(ct->transform, ct->rotation);
	ct->transform = m4_mul(ct->transform, ct->scale);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &ct->transform);
	
	if(printed < 2){
		printf("cube transform\n");
		m4_print(ct->transform);
		printed++;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, crpgTextureGetID(tex));

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void crpgCubePosition(crpgCube *c, vec3_t pos)
{
	Cube_t *ct = (Cube_t *)c;
	ct->translation = m4_translation(pos);
	printf("cube position\n");
	m4_print(ct->translation);
}

void crpgCubeScale(crpgCube *c, vec3_t scale)
{
	Cube_t *ct = (Cube_t *)c;
	ct->scale = m4_scaling(scale);
}

void crpgCubeRotation(crpgCube *c, float rot, vec3_t axis)
{
	Cube_t *ct = (Cube_t *)c;
	ct->rotation = m4_rotation(rot, axis);
}

crpgCube *crpgCubeNew()
{
	Cube_t *c = malloc(sizeof(Cube_t));
	crpgCube *ret = NULL;

	if(!initilised){
		initVertices();
		initShader(c);
	}

	ret = (crpgCube *) c;

	// sane defaults so the transform doesn't calculate to a matrix of 0.f's
	crpgCubePosition(ret, vec3(0.f, 0.f, 0.f));
	crpgCubeRotation(ret, 0.f, vec3(1.f, 1.f, 1.f));
	crpgCubeScale(ret, vec3(1.f, 1.f, 1.f));
	return ret;
}

void crpgCubeFree(crpgCube *c)
{
	free(c);
}
