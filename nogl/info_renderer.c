#include "info_renderer.h"
#include "point.h"

static WINDOW *win = NULL;
static Point2i winPos;
static Point2i winSize;
int layer = 0;

void irndr_init()
{
	Point2i termsize;
	getmaxyx(stdscr, termsize.y, termsize.x);
	winPos = point2i(0, termsize.y - 3);
	winSize = point2i(termsize.x, 3);
	win = newwin(winSize.y, winSize.x, winPos.y, winPos.x);
}

void irndr_render()
{
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	for(int i = 0; i < 20; ++i){
		mvwprintw(win, 1, 1, "Viewing layer %d", layer);
	}
	wrefresh(win);
}

void irndr_cleanup()
{
	// clearing the border
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	delwin(win);
}

void irndr_set_layer(int l)
{
	layer = l;
}
