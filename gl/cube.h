#ifndef CRPGCUBE_H
#define CRPGCUBE_H
#include "math_3d.h"

typedef struct {} crpgCube;

crpgCube *crpgCubeNew();
void crpgCubePosition(crpgCube *c, vec3_t pos);
void crpgCubeScale(crpgCube *c, vec3_t scale);
void crpgCubeRotation(crpgCube *c, float rot, vec3_t axis);
void crpgCubeRender(crpgCube *c);
void crpgCubeFree(crpgCube *c);
void crpgCubeSetCamera(crpgCube *c, mat4_t *cam);
#endif//CRPGCUBE_H
