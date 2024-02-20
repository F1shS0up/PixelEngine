#include "spark.h"
#include <algorithm>

spark::spark()
{
	initialColor = SDL_Color{ 235, 106, 42, 255 };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 1.6f;
	gravity = rand() % 10 + 70;
	conserveEnergyMultiplier = .05f;
	conserveEnergyLimit = 80;
	friction = 100.f;
	bounciness = 0.f;
	inertialResistance = 0.05f;
	explosionResistance = 0;
	fireResistance = 0;
	fireDamagePerSecond = 0.2f + ((float)(rand() % 1001) / 2000.f);
	fireSpreadDelay = 0;
	onFire = true;
}

spark::~spark()
{
}

void spark::Darken()
{
	color = SDL_Color
	{
		(Uint8)(color.r * std::clamp<float>(health * 2, 0, 1)),
		(Uint8)(color.g * std::clamp<float>(health * 2, 0, 1)),
		(Uint8)(color.b * std::clamp<float>(health * 2, 0, 1)),
		(Uint8)(color.a * std::clamp<float>(health * 4 + 0.5f, 0, 1))
	};
}

void spark::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{
	movable::Update(deltaTime, pxSim, x, y);
	Darken();
}
