#include "rubber.h"

rubber::rubber()
{
	initialColor = SDL_Color{ (Uint8)(rand() % 36 + 220), (Uint8)(rand() % 100), (Uint8)(rand() % 21 + 235), 255 };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 1.34f;
	gravity = 170.f;
	conserveEnergyMultiplier = .1f;
	conserveEnergyLimit = 100;
	friction = 100.f;
	bounciness = 0.6f;
	explosionResistance = 25;
	fireResistance = 80;
	fireSpreadDelay = 0.5f;
	fireDamagePerSecond = 0.5f;
}

rubber::~rubber()
{
}
void rubber::Darken()
{
	color = SDL_Color
	{
		(Uint8)(initialColor.r * health),
		(Uint8)(initialColor.g * health),
		(Uint8)(initialColor.b * health),
		(Uint8)(initialColor.a)
	};
}
