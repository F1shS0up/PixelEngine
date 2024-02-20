#pragma once
#include <unordered_map>
#include "entity.h"
#include "SDL.h"
#include "pixel_simulation.h"


class registry
{
public:
	void Init(entity_manager* eManager, SDL_Renderer* rend);
	void Update(double* deltaTime, entity_manager* eManager, class input_manager* inputManager);
	void Render(entity_manager* eManager, SDL_Renderer* rend, class input_manager* inputManager);

	pixel_simulation pixelSimulation;

};
