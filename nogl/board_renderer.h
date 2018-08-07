#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H
#include <ncurses.h>
#include "board.h"

void brndr_init();
void brndr_render();
void brndr_cleanup();
void brndr_set_board(Board *board);

#endif//BOARD_RENDERER_H
