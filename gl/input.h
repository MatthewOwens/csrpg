#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>

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
void crpgInputUpdate();
void crpgInputCleanup();

bool crpgInputPressed(int action);
bool crpgInputHeld(int action);
bool crpgInputReleased(int action);
#endif//INPUT_H
