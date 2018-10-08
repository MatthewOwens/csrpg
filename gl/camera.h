#ifndef CAMERA_H
#define CAMERA_H
#include "math_3d.h"
#include <stdbool.h>
typedef struct {} crpgCamera;

crpgCamera *crpgCameraNew(vec3_t from, vec3_t to, vec3_t up);
void crpgCameraFree(crpgCamera *c);
void crpgCameraPan(crpgCamera *c, vec3_t panAxis);
void crpgCameraSetAR(float ar);
mat4_t *crpgCameraGetMat(crpgCamera *c);
void crpgCameraSetSpeed(crpgCamera *c, float speedPerSecond);
void crpgCameraUpdate(crpgCamera *c, float dtms);
#endif//CAMERA_H
