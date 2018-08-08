#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H
#include <ncurses.h>
#include "board.h"

void brndr_init();
void brndr_render();
void brndr_cleanup();
void brndr_set_board(Board *board);
void brndr_set_rendered_layer(int l);
int brndr_get_rendered_layer();
void brndr_move_draw_pos(Point2i p);

#endif//BOARD_RENDERER_H
