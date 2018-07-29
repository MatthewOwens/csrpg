#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "board.h"
#include "point.h"

static Board* board = NULL;

bool init()
{
	if(SDL_Init(SDL_INIT_TIMER) < 0){
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	board = board_init(5,3);
	if(board == NULL){
		printf("ERROR: board null!\n");
		return false;
	}
	return true;
}

int main()
{
	if(!init())
		return -1;

	char *str = malloc(10);
	char *rot = malloc(4);
	Uint32 itime = SDL_GetTicks();
	Uint32 ctime = 0;
	int i = 0;
	Point2i loc;
	Tile* sel = NULL;

	for(int x = 0; x < 5; ++x){
		for(int y = 0; y < 3; ++y){
			loc.x = x;
			loc.y = y;
			sel = board_tile_at(board, loc);
			if(sel == NULL){
				printf("N");
			} else {
				printf("#");
			}
		}
		printf("\n");
	}

	strcpy(str, "Hello... |");
	strcpy(rot, "|/-\\");
	printf("%s", str);

	while(itime < ctime + 2000){
		str[9] = rot[i];
		printf("\r%s", str);

		++i;
		if(i > 3) i = 0;
		itime = SDL_GetTicks();
	}
	printf("\n");

	free(str);
	free(rot);
	SDL_Quit();

	return 0;
}
