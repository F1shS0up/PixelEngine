#include "water.h"

water::water()
{
	initialColor = SDL_Color{ (Uint8)(rand() % 10 + 20), (Uint8)(rand() % 20 + 40), 214, 155 };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 1.f;
	gravity = 140.f;
	liquidDispersionDir = rand() % 2;
	liquidDispersionDelay = 0.f;
	liquidDispersionCountdown = liquidDispersionDelay;
	explosionResistance = 7;
	fireResistance = 100;
}

water::~water()
{
}

void water::Darken()
{

}
