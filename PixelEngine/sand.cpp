#include "sand.h"
#include <algorithm>

sand::sand()
{
	initialColor = SDL_Color{ (Uint8)(rand() % 36 + 220), (Uint8)(rand() % 40 + 170), 80, 255 };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 2.f;
	gravity = 200.f;
	conserveEnergyMultiplier = .5f;
	conserveEnergyLimit = 80;
	friction = 100.f;
	bounciness = 0.f;
	inertialResistance = 0.f;
	explosionResistance = 1;
	fireResistance = 100;
}

sand::~sand()
{

}

void sand::Darken()
{
	color = SDL_Color
	{
		(Uint8)(initialColor.r * std::clamp<float>((health * 0.5 + 0.5f), 0, 1)),
		(Uint8)(initialColor.g * std::clamp<float>((health * 0.5 + 0.5f), 0, 1)),
		(Uint8)(initialColor.b * std::clamp<float>((health * 0.5 + 0.5f), 0, 1)),
		(Uint8)(initialColor.a)
	};
}
