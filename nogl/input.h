#ifndef INPUT_H
#define INPUT_H
enum Action{
	QUIT = 0,
	LAYER_UP,
	LAYER_DOWN,
	ERR_CLEAR,
	ACTION_LAST
};

enum Action input_update();
#endif//INPUT_H
