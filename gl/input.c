#include "input.h"
#include "err.h"

typedef struct KeyboardDevice{
	Uint8 state[SDL_NUM_SCANCODES];
	Uint8 prevState[SDL_NUM_SCANCODES];
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

static KeyboardDevice kb;
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
	kb.binds[INPUT_CAMERA_PAN_IN] = SDL_SCANCODE_W;
	kb.binds[INPUT_CAMERA_PAN_OUT] = SDL_SCANCODE_S;
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

	memset(kb.prevState, 0, sizeof(Uint8)*SDL_NUM_SCANCODES);
	memcpy(kb.state, SDL_GetKeyboardState(NULL), sizeof(Uint8)*SDL_NUM_SCANCODES);

	// constraining the mouse to the window
	// TODO: only set relative mouse mode once the mouse is in the window, disable input otherwise
	//SDL_SetRelativeMouseMode(SDL_TRUE);
}

void crpgInputCleanup()
{
	free(kb.binds);
}

void crpgInputUpdate(Uint32 windowFlags)
{
	bool windowShown = (windowFlags & SDL_WINDOW_SHOWN) ? true : false;
	bool windowMinimized = (windowFlags & SDL_WINDOW_MINIMIZED) ? true : false;
	bool windowInputFocus = (windowFlags & SDL_WINDOW_INPUT_FOCUS) ? true : false;

	if(!windowShown || windowMinimized)
		return;

	if(windowInputFocus){
		memcpy(kb.prevState, kb.state, sizeof(Uint8)*SDL_NUM_SCANCODES);
		memcpy(kb.state, SDL_GetKeyboardState(NULL), sizeof(Uint8)*SDL_NUM_SCANCODES);

		m.prevState = m.state;

		SDL_SetRelativeMouseMode(SDL_TRUE);
		m.state.buttons = SDL_GetMouseState(&(m.state.x), &(m.state.y));
		SDL_GetRelativeMouseState(&(m.state.relX), &(m.state.relY));
	} else {
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}
