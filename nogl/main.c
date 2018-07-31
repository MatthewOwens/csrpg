#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "board.h"
#include "point.h"
#include "ncurses.h"

static Board* board = NULL;

bool init()
{
	if(SDL_Init(SDL_INIT_TIMER) < 0){
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//initscr();
	return true;
}

int main()
{
	if(!init())
		return -1;

	board = board_init(point2i(5,3));
	if(board == NULL){
		fprintf(stderr, "board null after init!\n");
		return -1;
	}

	Uint32 itime = SDL_GetTicks();
	Uint32 ctime = 0;
	Point2i loc;
	Point2i bsize = board_get_size(board, "storing size");
	Uint32 cclock = SDL_GetTicks();
	Uint32 pclock = 0;

	// 'game' loop, only stays open for .5 seconds
	while(ctime < itime + 500){
		ctime = SDL_GetTicks();
	}

	SDL_Quit();
	//endwin();

	return 0;
}
