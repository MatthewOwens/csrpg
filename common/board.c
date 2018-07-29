#include "board.h"
#include <stdlib.h>

typedef struct {
	Tile **tiles;
	Point2i dimensions;
} Board_t;

Board *board_init(int sizex, int sizey)
{
	Board *ret = NULL;
	Board_t *b = malloc(sizeof(Board_t));
	int sizet = sizex * sizey;

	b->dimensions.x = sizex;
	b->dimensions.y = sizey;
	b->tiles = malloc(sizet * sizeof(Tile));

	for(int x = 0; x < sizex; ++x){
		for(int y = 0; y < sizey; ++y){

			b->tiles[y * sizex + x] =
			tile_init(point3i(x,y,1), PLAINS);
		}
	}

	ret = (Board *) b;
	return ret;
}

void board_cleanup(Board *b)
{
	Board_t *bt = (Board_t *) b;

	for(int i = 0; i < bt->dimensions.x; ++i){
		for(int j = 0; j < bt->dimensions.y; ++j){
			tile_cleanup(bt->tiles[i + (j*bt->dimensions.y)]);
		}
	}

	for(int j = 0; j < bt->dimensions.y; ++j){
		free(bt->tiles[j]);
	}
	free(bt->tiles);
}

Tile* board_tile_at(Board* b, Point2i point)
{
	Board_t *bt = (Board_t *) b;
	if (point.x > bt->dimensions.x || point.x < 0 ||
		point.y > bt->dimensions.y || point.y < 0 ){
		return NULL;
	}

	return bt->tiles[point.x + (point.y * bt->dimensions.y)];
}
