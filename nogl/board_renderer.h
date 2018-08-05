#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H
#include <ncurses.h>
#include "board.h"

void boardRenderer_init();
void boardRenderer_render();
void boardRenderer_cleanup();
void boardRenderer_set_board(Board *board);

#endif//BOARD_RENDERER_H
