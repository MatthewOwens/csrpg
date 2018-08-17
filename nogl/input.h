#ifndef INPUT_H
#define INPUT_H
enum Action{
	QUIT = 0,
	LAYER_UP,
	LAYER_DOWN,
	ERR_CLEAR,
	MAP_LEFT,
	MAP_DOWN,
	MAP_UP,
	MAP_RIGHT,
	ACTION_LAST
};

enum Action input_update();
#endif//INPUT_H
