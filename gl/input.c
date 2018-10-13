#include "input.h"
#include "err.h"
#include <SDL2/SDL.h>

typedef struct InputDevice{
	Uint8 *state;
	Uint8 *prevState;
	Uint8 *binds;
}InputDevice;

static InputDevice kb = {NULL,NULL,NULL};

bool devicesNotInitilised()
{
	if(kb.binds == NULL){
		err_output("Error: Can't bind keys, kbBinds is NULL!");
		return true;
	}
	return false;
}

void loadKeybinds()
{
	if(devicesNotInitilised()){
		return;
	}

	//TODO: change from static keybinds to keybinds loaded from a file
	kb.binds[INPUT_CAMERA_PAN_UP] = SDL_SCANCODE_W;
	kb.binds[INPUT_CAMERA_PAN_DOWN] = SDL_SCANCODE_S;
	kb.binds[INPUT_CAMERA_PAN_LEFT] = SDL_SCANCODE_A;
	kb.binds[INPUT_CAMERA_PAN_RIGHT] = SDL_SCANCODE_D;
	kb.binds[INPUT_CAMERA_PAN_IN] = SDL_SCANCODE_Q;
	kb.binds[INPUT_CAMERA_PAN_OUT] = SDL_SCANCODE_E;
}

bool crpgInputPressed(int action)
{
	if(devicesNotInitilised()){
		return false;
	}
	printf("binds is: %d, SDL is %d\n", kb.binds[action], SDL_SCANCODE_D);
	printf("current state: %d, prev state: %d\n\n", kb.state[kb.binds[action]], kb.prevState[kb.binds[action]]);
	return (kb.state[ kb.binds[action] ] && !kb.prevState[ kb.binds[action] ]);
}

bool crpgInputHeld(int action)
{
	if(devicesNotInitilised()){
		return false;
	}

	return (kb.state[ kb.binds[action] ] || kb.prevState[ kb.binds[action] ]);
}

bool crpgInputReleased(int action)
{
	if(devicesNotInitilised()){
		return false;
	}

	return (!kb.state[ kb.binds[action] ] && kb.prevState[ kb.binds[action] ]);
}


void crpgInputInit()
{
	kb.binds = malloc(sizeof(Uint8) * INPUT_LAST);
	loadKeybinds();
}

void crpgInputCleanup()
{
	free(kb.binds);
}

void crpgInputUpdate()
{
	//SDL_PumpEvents();
	kb.prevState = kb.state;
	kb.state = SDL_GetKeyboardState(NULL);
}
