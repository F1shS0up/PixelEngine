#include "smoke.h"

smoke::smoke()
{
	initialColor = SDL_Color{ 155, 155, 155, (Uint8)(rand() % 20 + 70) };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 0.0007f;
	gravity = 10.f;
	gasDispersionDir = rand() % 2;
	viscosity = 0.2f;
	viscosityCountdown = viscosity;
	explosionResistance = 1;
	fireResistance = 1000;
	damagePerSecond = ((float)(rand() % 1001) / 10000.f) + 0.05f;
}

smoke::~smoke()
{
}

void smoke::Darken()
{
	color = SDL_Color
	{
		(Uint8)(initialColor.r * health),
		(Uint8)(initialColor.g * health),
		(Uint8)(initialColor.b * health),
		(Uint8)(initialColor.a)
	};
}

void smoke::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{
	gas::Update(deltaTime, pxSim, x, y);
	AddHealth(-*deltaTime * damagePerSecond, pxSim, x, y);
}
