#include "registry.h"

void registry::Init(entity_manager* eManager, SDL_Renderer* rend)
{
	pixelSimulation.Init();
}

void registry::Update(double* deltaTime, entity_manager* eManager, input_manager* inputManager)
{
	pixelSimulation.Update(this, eManager, inputManager, deltaTime);
}

void registry::Render(entity_manager* eManager, SDL_Renderer* renderer, input_manager* inputManager)
{
	pixelSimulation.Render(this, eManager, renderer, inputManager);
}
