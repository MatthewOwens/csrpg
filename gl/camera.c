#include "camera.h"
#include <math.h>
#include <stdlib.h>

static vec3_t worldSpaceVec;
static float aspectRatio = 16.f/9.f;	// sane default for the aspect ratio

typedef struct
{
	vec3_t from, to, up;
	mat4_t camera, perspective, worldToScreen;
} Camera_t;

///TODO: figure out why this is failing
mat4_t recalcPerspective(float hFovDeg, float near, float far)
{
	float vFovDeg = 2 * atan( tan(hFovDeg/2) * aspectRatio );
	float vFovRad = vFovDeg * (M_PI/180.f);

	return m4_perspective(vFovRad, aspectRatio, near, far);
}

void crpgCameraSetAR(float ar)
{
	aspectRatio = ar;
}

crpgCamera *crpgCameraNew(vec3_t from, vec3_t to, vec3_t up)
{
	// ensuring that the world doesn't go mental
	worldSpaceVec = vec3(1, 1, -1);
	Camera_t *ct = malloc(sizeof(Camera_t));
	ct->from = from;
	ct->to = to;
	ct->up = up;
	ct->camera = m4_look_at(from, to, up);
	//ct->perspective = recalcPerspective(90.f, 1, 10);
	ct->perspective = m4_perspective(60, aspectRatio, 1, 10);
	ct->worldToScreen = m4_mul(ct->perspective, ct->camera);

	crpgCamera *c = (crpgCamera *) ct;
	return c;
}

void crpgCameraFree(crpgCamera *c)
{
	if(c == NULL){
		return;
	} else {
		free(c);
	}
}

void crpgCameraPan(crpgCamera *c, vec3_t pan)
{
	Camera_t *ct = (Camera_t *) c;
	ct->from.x += pan.x;
	ct->from.y += pan.y;
	ct->from.z += pan.z;

	// recalc camera matrices
	ct->camera = m4_look_at(ct->from, ct->to, ct->up);
	ct->worldToScreen = m4_mul(ct->perspective, ct->camera);
}

mat4_t *crpgCameraGetMat(crpgCamera *c)
{
	Camera_t *ct = (Camera_t *)c;
	return &(ct->worldToScreen);
}
