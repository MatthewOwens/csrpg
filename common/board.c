#include "board.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	Tile **tiles;
	Point2i dimensions;
} Board_t;

Board *board_init(Point2i size)
{
	Board *ret = NULL;
	Board_t *b = malloc(sizeof(Board_t));
	int sizet = size.x * size.y;

	b->dimensions.x = size.x;
	b->dimensions.y = size.y;
	b->tiles = malloc(sizet * sizeof(Tile));

	for(int x = 0; x < size.x; ++x){
		for(int y = 0; y < size.y; ++y){

			b->tiles[y * size.x + x] =
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

bool is_point_valid(Point2i d, Point2i p)
{
	return !(p.x > d.x || p.x < 0 ||
			 p.y > d.y || p.y < 0 );
}

Tile* board_tile_at(Board* b, Point2i point)
{
	Board_t *bt = (Board_t *) b;

	if(is_point_valid(bt->dimensions, point)){
		return bt->tiles[point.x + (point.y * bt->dimensions.y)];
	} else {
		return NULL;
	}
}

enum Terrain board_terrain_at(Board* b, Point2i point)
{
	Board_t *bt = (Board_t *) b;

	if(is_point_valid(bt->dimensions, point)){
		return tile_terrain(bt->tiles[point.x + (point.y * bt->dimensions.y)]);
	} else {
		return IMPASSABLE;
	}
}

int board_elevation_at(Board* b, Point2i point)
{
	Board_t *bt = (Board_t *) b;
	if(b == NULL)
		return -1;

	if(is_point_valid(bt->dimensions, point)){
		return tile_position(bt->tiles[point.x+(point.y*bt->dimensions.y)]).z;
	} else { 
		return -1;
	}
}

Point2i board_get_size(Board* b, const char *why)
{
	Board_t *bt = (Board_t *) b;
	if(b == NULL){
		fprintf(stderr, "error getting board size to %s, board is NULL!", why);
		return point2i(0,0);
	} else {
		return bt->dimensions;
	}
}
