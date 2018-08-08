#include <stdlib.h>
#include "err.h"
#include "tile_renderer.h"

static Board *b = NULL;
static const char repr[] = {'X', '.', '^', '\'', '~', '*', '|', '0'};
const static char col_repr = '#';
const static char air_repr = ' ';
const static char unk_repr = '?';

char trndr_repr(Tile *t, int dlayer)
{
	if(b == NULL || t == NULL){
		err_output("trndr_repr error, tile or board NULL");
		return unk_repr;
	}

	int tlayer = tile_position(t).z;
	int terrain = tile_terrain(t);

	if(terrain < 0 || terrain > LAST){
		err_output("trndr_repr error, terrain < 0 or terrain > LAST");
		return unk_repr;
	} else {
		if(tlayer > dlayer) { return col_repr; }
		else if(tlayer < dlayer) { return air_repr; }
		else return repr[tile_terrain(t)];
	}
}

void trndr_set_board(Board *board) { b = board; }
