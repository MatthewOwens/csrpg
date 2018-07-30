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
	char *terrain = malloc(bsize.x * bsize.y);
	char *elevation = malloc(bsize.x * bsize.y);
	char **sel = &terrain;
	Uint32 cclock = SDL_GetTicks();
	Uint32 pclock = 0;

	for(int y = 0; y < bsize.y; ++y){
		for(int x = 0; x < bsize.x; ++x){
			loc = point2i(x,y);
			elevation[y * bsize.x + x] = board_elevation_at(board, loc) + '0';
			//if(elevation[y * bsize.x + x] != 1){
			if(board_elevation_at(board, loc) != 1){
				printf("elevation error at (%d,%d)\n", loc.x, loc.y);
			}
			if(board_terrain_at(board, loc) == IMPASSABLE){
				terrain[y * bsize.x + x] = 'X';
			} else {
				terrain[y * bsize.x + x] = '.';
			}
		}
	}
	printf("\n");

	// 'game' loop, only stays open for 2 seconds
	while(ctime < itime + 2000){
		// checking if the display should change
		if(cclock - pclock > 200){
			if(sel == &terrain){
				sel = &elevation;
			} else {
				sel = &terrain;
			}
			pclock = cclock;

			printf("elevation? %s", (sel == &elevation) ? "true\n" : "false\n");

			for(int y = 0; y < bsize.y; ++y){
				for(int x = 0; x < bsize.x; ++x){
					printf("%c", (*sel)[y * bsize.x + x]);
				}
				printf("\n");
			}
		}

		ctime = SDL_GetTicks();
		cclock = SDL_GetTicks();
	}

	free(terrain);
	free(elevation);
	SDL_Quit();
	//endwin();

	return 0;
}
