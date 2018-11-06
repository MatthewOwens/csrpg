#ifndef INFO_RENDERER_H
#define INFO_RENDERER_H
#include <ncurses.h>

void irndr_init();
void irndr_render();
void irndr_cleanup();
void irndr_set_layer(int l);
#endif//INFO_RENDERER_H
