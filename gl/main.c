
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <math.h>
#include "shader.h"
#include "texture.h"
#include "err.h"
#include "stb/stb_image.h"
#include "math_3d.h"
#include "point.h"
#include "cube.h"

static SDL_Window *window = NULL;
static SDL_GLContext *context = NULL;
static int screen_width = 1280;
static int screen_height = 720;
static bool quit = false;
static Uint32 itime;

static float vertices[] = {
	// positions		// colours		 	// texture coords
	0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f, // bottom left
	-0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f  // top left
};

static unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

static unsigned int ebo;
static unsigned int vbo, vao;
static float blendVal = 0.2f;
static crpgShader *shader = NULL;
static crpgTexture *tex[2];
static crpgCube *cube = NULL;
static mat4_t projection, transform, camera, world_to_screen;
static vec3_t from, to, up, screenSpace, worldSpace;

static void initShapes()
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);

	// first shape
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // param is the location of the attrib to enable.
	// colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);	// unbinding vao, since we're done

	// loading our textures
	stbi_set_flip_vertically_on_load(true);
	tex[0] = crpgTextureNew("textures/wall.jpg");
	tex[1] = crpgTextureNew("textures/target.png");

	shader = crpgShaderNew("tri");
	crpgShaderUse(shader);
	crpgShaderSetInt(shader, "texture1", 0);
	crpgShaderSetInt(shader, "texture2", 1);
	crpgShaderSetFloat(shader, "blendVal", blendVal);

	transform = m4_translation(vec3(0.5, 0.5, 0.f));
	transform = m4_mul(transform, m4_scaling(vec3(.5f, .5f, 1.f)));
	transform = m4_mul(transform, m4_rotation(m_deg_to_rad(45.f), vec3(0.f, 0.f, 1.f)));

	printf("wall transform\n");
	m4_print(transform);
	unsigned int transformLoc = glGetUniformLocation(crpgShaderID(shader), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform);

	cube = crpgCubeNew();
	//crpgCubePosition(cube, vec3(1.5, 0.5, 0.f));
}

static void initView()
{
	projection = m4_perspective(60, (float)screen_width/(float)screen_height, 1, 10);
	//from = vec3(0, 0.5, 2);
	from = vec3(3,3,3);
	to = vec3(0,0,0);
	up = vec3(0,1,0);
	camera = m4_look_at(from, to, up);
	worldSpace = vec3(1, 1, -1);
	world_to_screen = m4_mul(projection, camera);
	screenSpace = m4_mul_pos(world_to_screen, worldSpace);

	crpgCubeSetCamera(cube, &world_to_screen);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
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
		if(e.type == SDL_KEYDOWN){
			if(e.key.keysym.sym == SDLK_k){
				blendVal += .2f;
				crpgShaderSetFloat(shader, "blendVal", blendVal);
			}
			if(e.key.keysym.sym == SDLK_j){
				blendVal -= .2f;
				crpgShaderSetFloat(shader, "blendVal", blendVal);
			}
		}
	}
}

static void render()
{
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	crpgShaderUse(shader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, crpgTextureGetID(tex[0]));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, crpgTextureGetID(tex[1]));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	crpgCubeRender(cube);	// Not rendering??

	SDL_GL_SwapWindow(window);
}

int main()
{
	if(!init())
		return -1;

	initShapes();
	initView();
	itime = SDL_GetTicks();

	while(!quit){
		update();
		render();
	}

	SDL_Quit();
	crpgCubeFree(cube);
	return 0;
}
