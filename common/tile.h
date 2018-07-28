#include "point.h"

enum Terrain{
	IMPASSABLE = -1,
	PLAINS,
	MOUNTAIN,
	S_WATER,
	D_WATER,
	WALL,
	FLOOR,
	ROAD
};

typedef struct {} Tile;

Tile *tile_init(Point3i pos, enum Terrain ter);
void tile_cleanup(Tile *t);
Point3i tile_position(Tile *t);
enum Terrain tile_terrain(Tile *t);
