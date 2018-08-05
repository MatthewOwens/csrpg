#ifndef BOARD_H
#define BOARD_H
#include "point.h"
#include "tile.h"

typedef struct {} Board;

Board *board_init(Point2i size);
void board_cleanup(Board* b);
Point2i board_get_size(Board* b);

enum Terrain board_terrain_at(Board* b, Point2i point);
int board_elevation_at(Board* b, Point2i point);
Tile* board_tile_at(Board* b, Point2i point);
#endif//BOARD_H
