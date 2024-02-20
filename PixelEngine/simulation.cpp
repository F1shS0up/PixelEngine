#include "simulation.h"
#include <iostream>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "options.h"
#include "SDL2_gfxPrimitives.h"
#include "registry.h"
#include "input_manager.h"

#define HandleError() \
	std::cout << "ERROR:" << SDL_GetError() << std::endl; \



simulation::simulation()
{
}
simulation::~simulation()
{
}

bool simulation::Running()
{
	return running;
}

void simulation::Init()
{
	InitSDL();

	//Set some vars and enable some stuff
	assetPath = SDL_GetBasePath();
	assetPath += "Assets/";
	reg = new registry();
	eManager = new entity_manager();
	inputManager = new input_manager(options::WND_WIDTH / options::REN_WIDTH, options::WND_HEIGHT / options::REN_HEIGHT);

	//After init
	SDL_RenderSetLogicalSize(renderer, options::REN_WIDTH, options::REN_HEIGHT);
	SDL_StopTextInput();
	IMG_Init(0);
	SDL_SetRenderDrawBlendMode(renderer, options::BLEND_MODE);

	reg->Init(eManager, renderer);
}


void simulation::InitSDL()
{
	running = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Sdl initialized!" << std::endl;

		window = SDL_CreateWindow("GAME NAME", options::WINDOW_CENTERED ? SDL_WINDOWPOS_CENTERED : 0, options::WINDOW_CENTERED ? SDL_WINDOWPOS_CENTERED : 0, options::WND_WIDTH, options::WND_HEIGHT, options::WINDOW_FLAGS);
		if (window != nullptr)
		{
			std::cout << "Window created! Size: " << options::WND_WIDTH << "x" << options::WND_HEIGHT << std::endl;
		}
		else
		{
			HandleError();
		}

		SDL_SetWindowSize(window, options::WND_WIDTH, options::WND_HEIGHT);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (window != nullptr)
		{
			std::cout << "Renderer created!" << std::endl;
		}
		else
		{
			HandleError();
		}
	}
	else
	{
		HandleError();
	}

	if (TTF_Init() < 0)
	{
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
	}
	if (options::WINDOW_FLAGS & SDL_WINDOW_FULLSCREEN)SDL_SetWindowGrab(window, SDL_TRUE);
}

void simulation::HandleEvents()
{
	SDL_Event evt;
	SDL_PollEvent(&evt);
	switch (evt.type)
	{
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN:
		switch (evt.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			running = false;
			break;
		}

	default:
		break;
	}
}

void simulation::Update(double* deltaTime)
{
	inputManager->Update();

	reg->Update(deltaTime, eManager, inputManager);

	inputManager->UpdatePrevInput();
}

void simulation::Render()
{
	SDL_SetRenderDrawColor(renderer, 61, 84, 161, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 75, 75, 75, 255);

	reg->Render(eManager, renderer, inputManager);

	SDL_RenderPresent(renderer);
}

void simulation::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
