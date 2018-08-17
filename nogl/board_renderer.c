#include "board_renderer.h"
#include "tile_renderer.h"
#include "point.h"
#include "err.h"

static Board *b = NULL;
static WINDOW *win = NULL;
static Point2i winPos;
static Point2i winSize;
static int layer = 0;
static Point2i drawPos;

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
	// Ensuring that the canvas is clear to prevent ghosting
	for(int y = 1; y < winSize.y - 1; ++y){
		mvwhline(win, y, 1, ' ', winSize.x - 2);
	}

	// Drawing the board itself
	Point2i bsize = board_get_size(b);
	for(int y = 0; y < bsize.y; ++y){
		for(int x = 0; x < bsize.x; ++x){
			Tile *t = board_tile_at(b, point2i(x,y));
			mvwaddch(win, drawPos.y+y, drawPos.x+x, trndr_repr(t, layer));
		}
	}
}

void brndr_init()
{
	Point2i termsize;

	winPos = point2i(0,0);
	drawPos = point2i(1,1);
	getmaxyx(stdscr, termsize.y, termsize.x);
	winSize = termsize;
	winSize.y -= 4;
	//winSize.y -= 2;

	win = newwin(winSize.y, winSize.x, winPos.y, winPos.x);
}

void brndr_render()
{
	draw_board();
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(win);
}

void brndr_set_board(Board *board)
{
	b = board;
	trndr_set_board(board);
}

void brndr_cleanup()
{
	// clearing the border
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	b = NULL;
	delwin(win);
}

void brndr_set_rendered_layer(int l)
{
	layer = l;
}

void brndr_move_draw_pos(Point2i p)
{
	drawPos.x += p.x;
	drawPos.y += p.y;
}

int brndr_get_rendered_layer()
{
	return layer;
}
