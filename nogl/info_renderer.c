#include "info_renderer.h"
#include "point.h"

static WINDOW *win = NULL;
static Point2i winPos;
static Point2i winSize;

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
	wrefresh(win);
}

void irndr_cleanup()
{
	// clearing the border
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	delwin(win);
}
