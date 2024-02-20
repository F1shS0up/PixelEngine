#include <iostream>
#include <chrono>
#include "options.h"
#include <Windows.h>
#include "simulation.h"
#include "SDL.h"

std::chrono::steady_clock::time_point Start = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point TickTack;

int main(int argc, char* argv[])
{
	simulation* sim = new simulation();

	SetProcessDPIAware();
	sim->Init();

	double desiredDeltaTime = options::MAX_FPS != 0 ? 1000 / options::MAX_FPS : 1;
	double deltaTime = 1;

	while (sim->Running())
	{
		srand(SDL_GetTicks());
		Start = std::chrono::steady_clock::now();
		if (options::MAX_FPS != 0 && deltaTime < desiredDeltaTime)
		{
			SDL_Delay(desiredDeltaTime - deltaTime);
		}

		sim->Update(&deltaTime);
		sim->HandleEvents();
		sim->Render();

		TickTack = std::chrono::steady_clock::now();

		deltaTime = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(TickTack - Start).count() / 1'000'000'000.0;
		std::cout << "FPS: " << 1 / deltaTime << std::endl;
	}

	sim->Clean();

	return 0;
}