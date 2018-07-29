#ifndef BOARD_H
#define BOARD_H
#include "point.h"
#include "tile.h"

typedef struct {} Board;

Board *board_init(int sizex, int sizey);
void board_cleanup(Board* b);
Tile* board_tile_at(Board* b, Point2i point);
#endif//BOARD_H
