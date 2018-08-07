#ifndef TILE_RENDERER
#define TILE_RENDERER
#include "tile.h"
#include "board.h"

char trndr_repr(Tile *t, int layer);
void trndr_set_board(Board *board);
#endif//TILE_RENDERER
