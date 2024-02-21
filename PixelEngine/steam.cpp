#include "steam.h"

steam::steam()
{
	initialColor = SDL_Color{ 255, 255, 255, (Uint8)(rand() % 20 + 80)};
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 0.00058f;
	gravity = 10.f;
	gasDispersionDir = rand() % 2;
	viscosity = 0.2f;
	viscosityCountdown = viscosity;
	explosionResistance = 0;
	fireResistance = 1000;
}

steam::~steam()
{
}

void steam::Darken()
{
	color = SDL_Color
	{
		(Uint8)(initialColor.r * health),
		(Uint8)(initialColor.g * health),
		(Uint8)(initialColor.b * health),
		(Uint8)(initialColor.a)
	};
}
