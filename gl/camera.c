#include <stdlib.h>
#include <math.h>
#include "camera.h"
#include "input.h"

static const float YAW			= -90.f;
static const float PITCH		= 0.0f;
static const float SPEED		= 0.2f;
static const float SENSITIVITY	= 0.1f;
static const float ZOOM			= 45.0f;

typedef struct
{
	vec3_t position;
	vec3_t front;
	vec3_t up;
	vec3_t right;
	vec3_t worldUp;

	/* euler angles */
	float yaw;
	float pitch;

	/* camera options */
	float movementSpeed;
	float mouseSensitivity;
	float zoom;
	float aspectRatio;
	float near;
	float far;

	/* storing the final matrix to prevent multiple calculations/frame */
	mat4_t matrix;
} crpgCamera_t;

double toRadians(double degrees)
{
	return degrees * (M_PI / 180.f);
}

double toDegrees(double radians)
{
	return radians * (180.f / M_PI);
}

void updateMatrix(crpgCamera_t *ct)
{
	vec3_t to = v3_add(ct->position, ct->front);

	mat4_t lookat = m4_look_at(ct->position, to, ct->up);
	/* TODO: change first param to calcualated value */
	mat4_t perspective = m4_perspective(60, ct->aspectRatio, ct->near, ct->far);
	ct->matrix = m4_mul(perspective, lookat);
}

void updateVectors(crpgCamera_t *ct)
{
	/* calculate the new front vector */
	ct->front.x = cos(toRadians(ct->yaw)) * cos(toRadians(ct->pitch));
	ct->front.y = sin(toRadians(ct->pitch));
	ct->front.z = sin(toRadians(ct->yaw)) * cos(toRadians(ct->pitch));
	ct->front = v3_norm(ct->front);

	/* calculating the new right and up vectors */
	ct->right = v3_norm(v3_cross(ct->front, ct->worldUp));
	ct->up = v3_norm(v3_cross(ct->right, ct->front));
}

mat4_t *crpgCameraGetMat(crpgCamera *c)
{
	crpgCamera_t *ct = (crpgCamera_t *)c;
	updateMatrix(ct);
	return &(ct->matrix);
}

crpgCamera *crpgCameraNew(vec3_t position, vec3_t up)
{
	crpgCamera_t *ct = malloc(sizeof(crpgCamera_t));
	ct->position = position;
	ct->up = up;
	ct->worldUp = vec3(0,1,0);

	/* using some sane defaults */
	ct->front = vec3(0.0f, 0.0f, -1.0f);
	ct->yaw = YAW;
	ct->pitch = PITCH;
	ct->zoom = ZOOM;
	ct->movementSpeed = SPEED;
	ct->mouseSensitivity = SENSITIVITY;
	ct->aspectRatio = 16.f/9.f;
	ct->near = 1.f;
	ct->far = 30.f;

	updateVectors(ct);

	crpgCamera *c = (crpgCamera *)ct;
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

void crpgCameraSetZoom(crpgCamera *c, float zoom)
{
	crpgCamera_t *ct = (crpgCamera_t *)c;
	ct->zoom = zoom;
}

void crpgCameraSetSpeed(crpgCamera *c, float speed)
{
	crpgCamera_t *ct = (crpgCamera_t *)c;
	ct->movementSpeed = speed;
}

void crpgCameraSetSensitivity(crpgCamera *c, float sensitivity)
{
	crpgCamera_t *ct = (crpgCamera_t *)c;
	ct->mouseSensitivity = sensitivity;
}

void crpgCameraUpdate(crpgCamera *c, float dtms)
{
	crpgCamera_t *ct = (crpgCamera_t *)c;
	float velocity = ct->movementSpeed * dtms;

	/* updating the pan values */
	if(crpgInputHeld(INPUT_CAMERA_PAN_IN)){
		ct->position = v3_add(ct->position, v3_muls(ct->front, velocity));
	}
	if(crpgInputHeld(INPUT_CAMERA_PAN_OUT)){
		ct->position = v3_sub(ct->position, v3_muls(ct->front, velocity));
	}
	if(crpgInputHeld(INPUT_CAMERA_PAN_RIGHT)){
		ct->position = v3_add(ct->position, v3_muls(ct->right, velocity));
	}
	if(crpgInputHeld(INPUT_CAMERA_PAN_LEFT)){
		ct->position = v3_sub(ct->position, v3_muls(ct->right, velocity));
	}
	if(crpgInputHeld(INPUT_CAMERA_PAN_UP)){
		ct->position = v3_add(ct->position, v3_muls(ct->worldUp, velocity));
	}
	if(crpgInputHeld(INPUT_CAMERA_PAN_DOWN)){
		ct->position = v3_sub(ct->position, v3_muls(ct->worldUp, velocity));
	}

	/* processing mouse movement */
	vec2_t mouseOffset = crpgInputMouseRelPos();
	mouseOffset.x *= ct->mouseSensitivity;
	mouseOffset.y *= ct->mouseSensitivity;

	ct->yaw += mouseOffset.x;
	ct->pitch -= mouseOffset.y;

	/* preventing the screen from flipping */
	ct->pitch = (ct->pitch > 89.0f) ? 89.0f : ct->pitch;
	ct->pitch = (ct->pitch < -89.0f) ? -89.0f : ct->pitch;

	/* constricting the yaw */
	ct->yaw = (ct->yaw < 0.f) ? 360.f : ct->yaw;
	ct->yaw = (ct->yaw > 360.f) ? 0.f : ct->yaw;

	printf("ct->pitch: %f\tct->yaw: %f\tpos: (%f,%f,%f)\r",
			ct->pitch, ct->yaw, ct->position.x, ct->position.y, ct->position.z);

	updateVectors(ct);
}

void crpgCameraRender(crpgCamera *c)
{
}
