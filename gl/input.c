#include "input.h"
#include "err.h"
#include <SDL2/SDL.h>

typedef struct KeyboardDevice{
	Uint8 *state;
	Uint8 *prevState;
	Uint8 *binds;
}KeyboardDevice;

typedef struct MouseState{
	Uint8 buttons;
	int x, y;
	int relX, relY;		// the xy coords relative to the last frame
}MouseState;

typedef struct MouseDevice{
	MouseState state;
	MouseState prevState;
}MouseDevice;

static KeyboardDevice kb = {NULL,NULL,NULL};
static MouseDevice m;	//Setting buttonCount to 5, as SDL supports 5 mouse buttons

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
	kb.binds[INPUT_CAMERA_PAN_UP] = SDL_SCANCODE_Q;
	kb.binds[INPUT_CAMERA_PAN_DOWN] = SDL_SCANCODE_E;
	kb.binds[INPUT_CAMERA_PAN_LEFT] = SDL_SCANCODE_A;
	kb.binds[INPUT_CAMERA_PAN_RIGHT] = SDL_SCANCODE_D;
	kb.binds[INPUT_CAMERA_PAN_IN] = SDL_SCANCODE_S;
	kb.binds[INPUT_CAMERA_PAN_OUT] = SDL_SCANCODE_W;
}

vec2_t crpgInputMousePos()
{
	return vec2(m.state.x, m.state.y);
}

vec2_t crpgInputMouseRelPos()
{
	return vec2(m.state.relX, m.state.relY);
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

	m.prevState = m.state;
	//m.state.buttons = SDL_GetRelativeMouseState(&(m.state.x), &(m.state.y));
	m.state.buttons = SDL_GetMouseState(&(m.state.x), &(m.state.y));
	SDL_GetRelativeMouseState(&(m.state.relX), &(m.state.relY));
}
