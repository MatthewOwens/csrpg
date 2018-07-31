#include "tile.h"
#include <stdlib.h>

typedef struct
{
	Point3i position;
	enum Terrain terrain;
} Tile_t;

static const char repr[] = {'X', '.', '^', '\'', '~', '#', '*', '|', '0'};

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
	Tile_t *tt = (Tile_t *) t;
	return tt->position;
}

enum Terrain tile_terrain(Tile *t)
{
	Tile_t *tt = (Tile_t *) t;
	return tt->terrain;
}

char tile_repr(enum Terrain t)
{
	if(t < 0 || t > LAST){
		return '?';
	} else {
		return repr[t];
	}
}
