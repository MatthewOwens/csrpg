#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "board.h"
#include "point.h"
#include <ncurses.h>

static Board* board = NULL;

bool init()
{
	if(SDL_Init(SDL_INIT_TIMER) < 0){
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	initscr();
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

	board = board_init(point2i(3,3));
	if(board == NULL){
		fprintf(stderr, "board null after init!\n");
		return -1;
	}

	Uint32 itime = SDL_GetTicks();
	Uint32 ctime = 0;
	Point2i loc;
	Point2i bsize = board_get_size(board, "storing size");
	Uint32 cclock = 0;
	Uint32 pclock = SDL_GetTicks();
	Point2i rpos = point2i(10,10); // where to draw the arr

	char *reprs = malloc(bsize.x * bsize.y * sizeof(char));
	char *elevs = malloc(bsize.x * bsize.y * sizeof(char));
	char *sel = NULL;

	for(int y = 0; y < bsize.y; ++y){
		for(int x = 0; x < bsize.x; ++x){
			elevs[x + (bsize.x * y)] =
				board_elevation_at(board, point2i(x, y)) + '0';
			reprs[x + (bsize.x * y)] =
				tile_repr(board_terrain_at(board, point2i(x, y)));
		}
	}

	draw_borders();

	// 'game' loop
	while(ctime < itime + 5000){
		ctime = SDL_GetTicks();
		cclock = SDL_GetTicks();
		
		// Switching the selection if needed
		if(cclock > pclock + 500 || pclock == 0){
			sel = (sel == reprs) ? elevs : reprs;
			pclock = cclock;

			for(int y = 0; y < bsize.y; ++y){
				for(int x = 0; x < bsize.x; ++x){
					mvaddch(y + rpos.y, x + rpos.x , sel[x + bsize.x * y]);
				}
			}
			refresh();
		}
	}


	SDL_Quit();
	endwin();

	return 0;
}
