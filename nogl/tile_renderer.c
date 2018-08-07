#include "tile_renderer.h"
#include "board.h"

static Board *b = NULL;
static const char repr[] = {'X', '.', '^', '\'', '~', '*', '|', '0'};
const static char col_repr = '#';
const static char air_repr = ' ';
const static char unk_repr = '?';

char trndr_repr(Tile *t, int dlayer)
{
	if(b == NULL || t == NULL)
		return unk_repr;

	int tlayer = tile_position(t).z;
	int terrain;

	if(t < 0; || t > LAST){
		return unk_repr;
	} else {
		if(tlayer < dlayer) { return col_repr; }
		else if(tlayer > dlayer) { return air_repr; }
		else return repr[tile_terrain(t)];
	}
}

void trendr_set_board(Board *board) { b = board; }
