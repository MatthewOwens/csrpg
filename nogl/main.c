#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "board.h"
#include "point.h"
#include "board_renderer.h"
#include "err.h"
#include <ncurses.h>

static Board* board = NULL;

bool init()
{
	if(SDL_Init(SDL_INIT_TIMER) < 0){
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	initscr();
	boardRenderer_init();
	curs_set(false);
	return true;
}

void draw_borders()
{
	char c = 'X';

	for(int i = 0; i < 80; ++i){
		mvaddch(0, i, c);
		mvaddch(22, i, c);
		mvaddch(24, i, c);
	}

	for(int i = 0; i < 25; ++i){
		mvaddch(i, 0, c);
		mvaddch(i, 79, c);
	}

	// updating the screen
	refresh();
}

int main()
{
	if(!init())
		return -1;

	board = board_init(point2i(4,3));
	if(board == NULL){
		fprintf(stderr, "board null after init!\n");
		return -1;
	}
	boardRenderer_set_board(board);

	boardRenderer_render();
	getchar();
	err_enable_logging("test");
	//refresh();
	getchar();
	err_clear();
	boardRenderer_render();
	getchar();

	SDL_Quit();
	boardRenderer_cleanup();
	endwin();

	return 0;
}
