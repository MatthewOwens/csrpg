#ifndef TIMESTEP_H
#define TIMESTEP_H
#include <stdbool.h>

void crpgTimeStepInit(float desiredFPS);
void crpgTimeStepSetDesiredFT(float desiredUpdateFT);
void crpgTimeStepUpdate();
bool crpgTimeStepPhysRequired(int updatesThisFrame);
float crpgTimeStepDelta();
#endif//TIMESTEP_H
