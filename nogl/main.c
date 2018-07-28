#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
//#include "tile.h"


//static Tile *tile = NULL;
//static Point3 pos;

bool init()
{
	if(SDL_Init(SDL_INIT_TIMER) < 0){
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
/*
	pos.x = 1;
	pos.y = 2;
	pos.z = 3;

	tile = tile_init(pos, Terrain.D_WATER);

	pos.x = pos.y = pos.z = 0;
	pos = tile_position(t);

	if(tile == NULL){
		printf("ERROR: tile null!");
		return false;
	}
*/
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

/*
	printf("Tile pos - (%d,%d,%d), ter - %d",
			pos.x, pos.y, pos.z, tile_terrain(t));
*/
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
