#ifndef CAMERA_H
#define CAMERA_H
#include "math_3d.h"

typedef struct {} crpgCamera;

crpgCamera *crpgCameraNew(vec3_t position, vec3_t up);
void crpgCameraFree(crpgCamera *c);
mat4_t *crpgCameraGetMat(crpgCamera *c);
void crpgCameraSetZoom(crpgCamera *c, float zoom);
void crpgCameraSetSpeed(crpgCamera *c, float speed);
void crpgCameraSetSensitivity(crpgCamera *c, float sensitivity);

void crpgCameraUpdate(crpgCamera *c, float dtms);
void crpgCameraRender(crpgCamera *c);
#endif//CAMERA_H
