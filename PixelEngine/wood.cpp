#include "wood.h"
inline float RandomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}


wood::wood()
{
	initialColor = SDL_Color{ (Uint8)(rand() % 20 + 130), (Uint8)(rand() % 10 + 90), (Uint8)(rand() % 10 + 50), 255 };
	color = initialColor;
	updated = false;
	density = 3.f;
	explosionResistance = 75;
	fireResistance = 30;
	fireSpreadDelay = 0.65f + (RandomFloat() - 0.5f) / 4;
	fireDamagePerSecond = 0.25f + (RandomFloat() - 0.5f) / 8;
	sparkSpawnChance = 60;
}

wood::~wood()
{
}

void wood::Darken()
{
	color = SDL_Color
	{
		(Uint8)(initialColor.r * health),
		(Uint8)(initialColor.g * health),
		(Uint8)(initialColor.b * health),
		(Uint8)(initialColor.a)
	};
}
