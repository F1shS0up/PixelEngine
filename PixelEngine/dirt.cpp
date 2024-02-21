#include "dirt.h"
#include <algorithm>

dirt::dirt()
{
	initialColor = SDL_Color{ (Uint8)(rand() % 20 + 117), (Uint8)(rand() % 20 + 60), (Uint8)(rand() % 23 + 33), 255 };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 3.4f;
	gravity = 190.f;
	conserveEnergyMultiplier = .2f;
	conserveEnergyLimit = 50;
	friction = 150.f;
	bounciness = 0.f;
	inertialResistance = 0.5f;
	explosionResistance = 38;
	fireResistance = 100;
}

dirt::~dirt()
{
}
void dirt::Darken()
{
	color = SDL_Color
	{
		(Uint8)(initialColor.r * std::clamp<float>((health * 0.5 + 0.5f), 0, 1)),
		(Uint8)(initialColor.g * std::clamp<float>((health * 0.5 + 0.5f), 0, 1)),
		(Uint8)(initialColor.b * std::clamp<float>((health * 0.5 + 0.5f), 0, 1)),
		(Uint8)(initialColor.a)
	};
}
