#include "input.h"
#include "stdio.h"
#include "err.h"

static char keys[] = {'q', 'K', 'J', 'c'};

enum Action input_update()
{
	char c = getchar();
	enum Action ret = ACTION_LAST;

	for(int i = 0; i < ACTION_LAST; ++i){
		if(c == keys[i]){
			return i;
		}
	}

	char msg[80];
	sprintf(msg, "character %c not recognised!", c);
	err_output(msg);
	return ret;
}
