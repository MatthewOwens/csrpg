#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "shaderLoader.h"
#include "err.h"

static SDL_Window *window = NULL;
static SDL_GLContext *context = NULL;
static int screen_width = 1280;
static int screen_height = 720;

static float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

static unsigned int vbo, vao;
static unsigned int vertShader, fragShader, shaderProgram;
static GLchar *vertSrc = NULL;
static GLchar *fragSrc = NULL;

static void initTri()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	vertSrc = shader_load_src("tri", VERTEX);
	shader_compile(vertShader, vertSrc, "triangle vertex");

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragSrc = shader_load_src("tri", FRAGMENT);
	shader_compile(fragShader, fragSrc, "triangle fragment");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	/*
	 * The glVertexAttribPointer call is rather complex, so I will document it
	 * here.
	 * The 1st paramater specifies the vertex attrib to configure. We want to
	 * configure the position attribute, as specified with:
	 * layout (location = 0) in tri.vert.
	 * The 2nd paramater specifies the size of the attribute to configure.
	 * We are using a vec3 value in the shader which is composed of 3 values.
	 * The 3rd specifies the data type of the paramater.
	 * The 4th specifies if the value should be normalised.
	 * The 5th specifies the size of the stride and the 6th is the offset.
	 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // param is the location of the attrib to enable.

	// cleaning up
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	shader_free_src(vertSrc);
	shader_free_src(fragSrc);
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

static void render()
{
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	SDL_GL_SwapWindow(window);
}

int main()
{
	Uint32 itime;
	Uint32 ctime = 0;
	SDL_Event e;

	if(!init())
		return -1;

	initTri();
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
