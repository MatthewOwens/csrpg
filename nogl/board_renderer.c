#include "board_renderer.h"
#include "point.h"
#include "err.h"

static Board *b = NULL;
static WINDOW *win = NULL;
static Point2i winPos;
static Point2i winSize;

void draw_board()
{
	if(b == NULL){
		err_output("cannot draw board, board is null!");
		return;
	}

	if(win == NULL){
		err_output("cannot draw boar, window is null!");
		return;
	}

	Point2i bsize = board_get_size(b);
	for(int y = 0; y < bsize.y; ++y){
		for(int x = 0; x < bsize.x; ++x){
			mvwaddch(win, 1+y, 1+x, '#');
		}
	}
}

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
	draw_board();
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
