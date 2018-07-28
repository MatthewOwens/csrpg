#include "tile.h"
#include <stdlib.h>

typedef struct
{
	Point3i position;
	enum Terrain terrain;
} Tile_t;

Tile *tile_init(Point3i pos, enum Terrain ter)
{
	Tile_t *t = malloc(sizeof(Tile_t));
	t->position = pos;
	t->terrain = ter;
	return (Tile *) t;
}

void tile_cleanup(Tile *t)
{
	free(t);
}

Point3i tile_position(Tile *t)
{
	Tile_t *tt = (Tile *) t;
	return tt->position;
}

enum Terrain tile_terrain(Tile *t)
{
	Tile_t *tt = (Tile *) t;
	return tt->terrain;
}
