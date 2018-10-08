#include "camera.h"
#include <math.h>
#include <stdlib.h>

static vec3_t worldSpaceVec;
static float aspectRatio = 16.f/9.f;	// sane default for the aspect ratio

typedef struct
{
	vec3_t from, to, up;
	mat4_t camera, perspective, worldToScreen;
	float speed;

	// Axis' to manouver across. If 0, no movement is occuring
	vec3_t pan, yaw, roll;
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
	ct->speed = 1.0f;

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

void crpgCameraSetSpeed(crpgCamera *c, float speedPerSecond)
{
	if(c == NULL) return;

	Camera_t *ct = (Camera_t *) c;
	ct->speed = speedPerSecond;
}

// This function expects a vec3_t formatted with values of 1, 0 or -1.
// to represent if the axis should be panned across and the direction
void crpgCameraPan(crpgCamera *c, vec3_t panAxis)
{
	if(c == NULL)
		return;

	Camera_t *ct = (Camera_t *) c;
	ct->pan = panAxis;

}

mat4_t *crpgCameraGetMat(crpgCamera *c)
{
	Camera_t *ct = (Camera_t *)c;
	return &(ct->worldToScreen);
}

// expecting components as {from, to, up}
void updatePan(vec3_t panAxis, vec3_t *components[3], float speed, float dtms)
{
	int axis[] = { panAxis.x, panAxis.y, panAxis.z };
	float* fromArr[] = { &components[0]->x, &components[0]->y, &components[0]->z };
	float* toArr[] = { &components[1]->x, &components[1]->y, &components[1]->z };

	for(int i = 0; i < 3; ++i){
		if(axis[i] != 0){	// if we should pan on this axis
			int sign = 0;
			sign = (axis[i] > 0) ? 1 : -1;
			*fromArr[i] += sign * (speed/1000.f);
			*toArr[i] += sign * (speed/1000.f);
		}
	}
}

void crpgCameraUpdate(crpgCamera *c, float dtms)
{
	Camera_t *ct = (Camera_t *)c;
	vec3_t *components[] = { &(ct->from), &(ct->to), &(ct->up) };

	updatePan(ct->pan, components, ct->speed, dtms);

	// recalc camera matrices
	ct->camera = m4_look_at(ct->from, ct->to, ct->up);
	ct->worldToScreen = m4_mul(ct->perspective, ct->camera);
}
