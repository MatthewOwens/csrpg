#ifndef TILE_H
#define TILE_H
#include "point.h"

enum Terrain{
	IMPASSABLE = 0,
	PLAIN,
	MOUNTAIN,
	S_WATER,
	D_WATER,
	WALL,
	FLOOR,
	ROAD,
	LAST
};


typedef struct {} Tile;

Tile *tile_init(Point3i pos, enum Terrain ter);
void tile_cleanup(Tile *t);
Point3i tile_position(Tile *t);
enum Terrain tile_terrain(Tile *t);

// TODO: move to nogl output c file
char tile_repr(enum Terrain t);
#endif//TILE_H
