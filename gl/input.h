#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>
#include "math_3d.h"
#include <SDL2/SDL.h>

typedef enum crpgInputActions{
	INPUT_CAMERA_PAN_DOWN = 0,
	INPUT_CAMERA_PAN_UP,
	INPUT_CAMERA_PAN_LEFT,
	INPUT_CAMERA_PAN_RIGHT,
	INPUT_CAMERA_PAN_IN,
	INPUT_CAMERA_PAN_OUT,
	INPUT_LAST
}crpgInputActions;

void crpgInputInit();
void crpgInputUpdate(Uint32 windowFlags);
void crpgInputCleanup();

bool crpgInputPressed(int action);
bool crpgInputHeld(int action);
bool crpgInputReleased(int action);
vec2_t crpgInputMousePos();
vec2_t crpgInputMouseRelPos();
#endif//INPUT_H
