#include "err.h"
#include <stdio.h>
#include <ncurses.h>
#include "point.h"

static WINDOW *win = NULL;
static char* lpath = NULL;

#define ERR_X 0
#define ERR_Y 0
#define ERR_W 80
#define ERR_H 3

void err_output(const char *message)
{
	if(stdscr == NULL){	// ncurses not initilised
		fprintf(stderr, message);
	} else {
		err_clear();
		win = newwin(ERR_H, ERR_W, ERR_Y, ERR_X);
		wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
		mvwprintw(win, 1, 2, message);
		wrefresh(win);
	}
}

void err_enable_logging(const char* logpath)
{
	err_output("logging not yet implemented");
}

void err_clear()
{
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(win);
	delwin(win);
	win = NULL;
}
