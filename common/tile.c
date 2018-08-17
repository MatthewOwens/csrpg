#include "tile.h"
#include "err.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CLAMPERR "Tile init error! z-coord must be 0-9, clamping to %d\n"

typedef struct
{
	Point3i position;
	enum Terrain terrain;
} Tile_t;


Tile *tile_init(Point3i pos, enum Terrain ter)
{
	Tile_t *t = malloc(sizeof(Tile_t));
	bool clamped = false;
	char msg[80];

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
		sprintf(msg, CLAMPERR, t->position.z);
		err_output(msg);
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
