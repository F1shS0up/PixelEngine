#include "oil.h"
#include <iostream>

inline float RandomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

oil::oil()
{
	initialColor = SDL_Color{ (Uint8)(rand() % 10 + 51), (Uint8)(rand() % 20 + 30), (Uint8)(rand() % 10 + 20), 255 };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 1.9f;
	gravity = 140.f;
	liquidDispersionDir = rand() % 2;
	liquidDispersionDelay = 0.1f;
	liquidDispersionCountdown = liquidDispersionDelay;
	explosionResistance = 7;
	fireResistance = -1;
	fireSpreadDelay = 0.025f + (float)(RandomFloat() - 0.5f) / 100.f;
	fireDamagePerSecond = (float)(RandomFloat() / 2.f) + 0.4f;
	sparkSpawnChance = 2;
}

void oil::Darken()
{
}
