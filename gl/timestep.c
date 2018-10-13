#include "timestep.h"
#include <SDL2/SDL.h>
#include <math.h>

static const int MAX_PHYSICS_STEPS = 6;
static const float MAX_DELTA_TIME = 1.f;
static const float MS_PER_SECOND = 1000.f;

static float desiredFrameTime;
static Uint32 currentT;
static Uint32 prevT;
static float frameTime;
static float totalDeltaTime;
static float deltaTime;

float crpgTimeStepDelta()
{
	return deltaTime;
}

void crpgTimeStepSetDesiredFT(float desiredFPS)
{
	desiredFrameTime = MS_PER_SECOND/desiredFPS;
}

void crpgTimeStepInit(float desiredFPS)
{
	crpgTimeStepSetDesiredFT(desiredFPS);

	currentT = SDL_GetTicks();
	prevT = SDL_GetTicks();
}

void crpgTimeStepUpdate()
{
	prevT = currentT;
	currentT = SDL_GetTicks();
	frameTime = currentT - prevT;
	totalDeltaTime = frameTime / desiredFrameTime;
}

bool crpgTimeStepPhysRequired(int updatesThisFrame)
{
	if(totalDeltaTime <= 0.f || updatesThisFrame >= MAX_PHYSICS_STEPS){
		return false;
	}

	deltaTime = fminf(totalDeltaTime, MAX_DELTA_TIME);
	totalDeltaTime -= deltaTime;
	return true;
}
