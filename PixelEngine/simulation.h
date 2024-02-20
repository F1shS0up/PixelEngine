#pragma once
#include "SDL.h"
#include <string>

class simulation
{
public:
	simulation();
	~simulation();

	bool Running();
	void Init();
	void InitSDL();

	void HandleEvents();
	void Update(double* deltaTime);
	void Render();
	void Clean();


	SDL_Window* window;
	SDL_Renderer* renderer;

	class registry* reg;
	class entity_manager* eManager;
	class input_manager* inputManager;

	std::string assetPath;

private:
	bool running;
};
