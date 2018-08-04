#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CLAMPERR "Tile init error! z-coord must be 0-9, clamping to %d\n"

typedef struct
{
	Point3i position;
	enum Terrain terrain;
} Tile_t;

static const char repr[] = {'X', '.', '^', '\'', '~', '#', '*', '|', '0'};

Tile *tile_init(Point3i pos, enum Terrain ter)
{
	Tile_t *t = malloc(sizeof(Tile_t));
	bool clamped = false;

	t->position = pos;
	t->terrain = ter;
	if(pos.z < 0){
		clamped = true;
		t->position.z = 0;
	} else if (pos.z > 9) {
		clamped = true;
		t->position.z = 9;
	}
	if(clamped == true){
		//TODO: err output
		//fprintf(stderr, CLAMPERR, t->position.z);
	}

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
