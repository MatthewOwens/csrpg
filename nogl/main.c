#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <ncurses.h>
#include "board.h"
#include "point.h"
#include "board_renderer.h"
#include "err.h"
#include "input.h"

static Board* board = NULL;

bool init()
{
	if(SDL_Init(SDL_INIT_TIMER) < 0){
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	initscr();
	brndr_init();
	curs_set(false);
	return true;
}

int main()
{
	int layer = 0;

	if(!init())
		return -1;

	board = board_init(point2i(4,3));
	bool quit = false;
	if(board == NULL){
		fprintf(stderr, "board null after init!\n");
		return -1;
	}
	brndr_set_board(board);
	brndr_set_rendered_layer(layer);

	brndr_render();

	while(!quit){
		switch(input_update()){
			case QUIT:
				quit = true;
				break;
			case LAYER_UP:
				if(layer < 9){
					layer++;
				}
				brndr_set_rendered_layer(layer);
				brndr_render();
				break;
			case LAYER_DOWN:
				if(layer > 0){
					layer--;
				}
				brndr_set_rendered_layer(layer);
				brndr_render();
				break;
			case ERR_CLEAR:
				err_clear();
				break;
			case MAP_LEFT:
				brndr_move_draw_pos(point2i(-1,0));
				brndr_render();
				break;
			case MAP_RIGHT:
				brndr_move_draw_pos(point2i(1,0));
				brndr_render();
				break;
			case MAP_UP:
				brndr_move_draw_pos(point2i(0,-1));
				brndr_render();
				break;
			case MAP_DOWN:
				brndr_move_draw_pos(point2i(0,1));
				brndr_render();
				break;
		}
	}

	SDL_Quit();
	brndr_cleanup();
	endwin();

	return 0;
}
