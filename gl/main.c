#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <math.h>
#include "shader.h"
#include "err.h"

static SDL_Window *window = NULL;
static SDL_GLContext *context = NULL;
static int screen_width = 1280;
static int screen_height = 720;
static bool quit = false;
static Uint32 itime;

static float vertices[] = {
	// positions		// colors
	0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	// top right
	0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	// bottom right
	-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	// bottom left
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f	// top left
};

static unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

static unsigned int ebo;
static unsigned int vbo, vao;
Shader *shader = NULL;

static void initShapes()
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);

	// first shape
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // param is the location of the attrib to enable.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);	// unbinding vao, since we're done
	shader = crpgShaderNew("tri");
}

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

static void update()
{
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0){
		if(e.type == SDL_QUIT){
			quit = true;
		}
	}
}

static void render()
{
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	crpgShaderUse(shader);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SDL_GL_SwapWindow(window);
}

int main()
{
	if(!init())
		return -1;

	initShapes();
	itime = SDL_GetTicks();

	while(!quit){
		update();
		render();
	}

	SDL_Quit();
	return 0;
}
