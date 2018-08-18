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
	0.0f, 0.5f, 0.0f,		// top right
	0.0f, -0.5f, 0.0f,		// bottom right
	-1.0f, -0.5f, 0.0f,		// bottom left
	-1.0f, 0.5f, 0.0f		// top left
};

static float vertices2[] = {
	1.0f, 0.5f, 0.0f,		// top right
	1.0f, -0.5f, 0.0f,		// bottom right
	0.0f, -0.5f, 0.0f,		// bottom left
	0.0f, 0.5f, 0.0f		// top left
};

static unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

static unsigned int ebo;
static unsigned int vbos[2], vaos[2];
static unsigned int vertShader[2], fragShader[2], shaderProgram[2];
static GLchar *vertSrc[2];
static GLchar *fragSrc[2];

static void initShapes()
{
	glGenBuffers(2, vbos);
	glGenVertexArrays(2, vaos);
	glGenBuffers(1, &ebo);

	// first shape
	glBindVertexArray(vaos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // param is the location of the attrib to enable.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// second shape
	glBindVertexArray(vaos[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);	// unbinding vao, since we're done

	vertSrc[0] = shader_load_src("tri", VERTEX);
	vertSrc[1] = shader_load_src("tri2", VERTEX);
	fragSrc[0] = shader_load_src("tri", FRAGMENT);
	fragSrc[1] = shader_load_src("tri2", FRAGMENT);

	for(int i = 0; i < 2; ++i){
		vertShader[i] = glCreateShader(GL_VERTEX_SHADER);
		shader_compile(vertShader[i], vertSrc[i], "vertex");
		fragShader[i] = glCreateShader(GL_FRAGMENT_SHADER);
		shader_compile(fragShader[i], fragSrc[i], "Fragment");

		shaderProgram[i] = glCreateProgram();
		glAttachShader(shaderProgram[i], vertShader[i]);
		glAttachShader(shaderProgram[i], fragShader[i]);
		glLinkProgram(shaderProgram[i]);

		// cleaning up
		glDeleteShader(vertShader[i]);
		glDeleteShader(fragShader[i]);
		shader_free_src(vertSrc[i]);
		shader_free_src(fragSrc[i]);
	}
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(shaderProgram[0]);
	glBindVertexArray(vaos[0]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(shaderProgram[1]);
	glBindVertexArray(vaos[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	SDL_GL_SwapWindow(window);
}

int main()
{
	Uint32 itime;
	Uint32 ctime = 0;
	SDL_Event e;

	if(!init())
		return -1;

	initShapes();
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
