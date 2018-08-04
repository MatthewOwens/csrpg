#include "err.h"
#include <stdio.h>
#include <ncurses.h>
#include "point.h"

char* lpath = NULL;
static const char lendchar = '+';
static const char lchar = '-';

void err_output(const char *message)
{
	Point2i scrsize = point2i(0,0);

	if(stdscr == NULL){	// ncurses not initilised
		fprintf(stderr, message);
	} else {
		err_clear();
		getmaxyx(stdscr, scrsize.y, scrsize.x);
		mvprintw(5, 5, message);
	}
}

void err_enable_logging(const char* logpath)
{
	err_output("logging not yet implemented");
}

void err_clear()
{
	Point2i msgpos;
	getmaxyx(stdscr, msgpos.y, msgpos.x);

	mvaddch(msgpos.y, 0, lendchar);
	mvaddch(msgpos.y, msgpos.x, lendchar);

	for(int i = 1; i < msgpos.y; ++i){
		mvaddch(msgpos.y, i, lchar);
	}
}
