#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

static SDL_Window *window = NULL;
static SDL_GLContext *context = NULL;
static int screen_width = 1280;
static int screen_height = 720;

static bool init()
{
	if (SDL_Init(
		SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS
		) < 0){
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("csrpg - opengl", SDL_WINDOWPOS_CENTERED,
			 SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == NULL){
		printf("SDL couldn't make an OpenGL window! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	context = SDL_GL_CreateContext(window);

	if(context == NULL){
		printf("SDL couldn't create an OpenGL context! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	/* syncing the buffer swap with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);
	glViewport(0, 0, screen_width, screen_height);

	glewExperimental = GL_TRUE;
	glewInit();

	return true;
}

static void render()
{
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

int main()
{
	Uint32 itime;
	Uint32 ctime = 0;
	SDL_Event e;

	if(!init())
		return -1;

	itime = SDL_GetTicks();


	while(ctime != itime + 10000){
		ctime = SDL_GetTicks();

		while(SDL_PollEvent(&e) != 0){
			if (e.type == SDL_QUIT){
				printf("quitting!\n");
				ctime = itime + 10000;
			}
		}

		render();
	}

	SDL_Quit();
	return 0;
}
