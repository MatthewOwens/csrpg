#include "board_renderer.h"
#include "point.h"

static Board *b = NULL;
static WINDOW *win = NULL;
static Point2i winPos;
static Point2i winSize;

void boardRenderer_init()
{
	Point2i termsize;

	winPos = point2i(0,0);
	getmaxyx(stdscr, termsize.y, termsize.x);
	winSize = termsize;
	winSize.y -= 2;

	win = newwin(winSize.y, winSize.x, winPos.y, winPos.x);
}

void boardRenderer_render()
{
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(win);
}

void boardRenderer_set_board(Board *board)
{
	b = board;
}

void boardRenderer_cleanup()
{
	// clearing the border
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	b = NULL;
	delwin(win);
}
