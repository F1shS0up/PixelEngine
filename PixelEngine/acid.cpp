#include "acid.h"


acid::acid()
{
	initialColor = SDL_Color{ (Uint8)(rand() % 36 + 180), (Uint8)(rand() % 40 + 215), 0, 155 };
	color = initialColor;
	updated = false;
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	density = 1.0031f;
	gravity = 150.f;
	liquidDispersionDir = rand() % 2;
	liquidDispersionDelay = 0.03f;
	liquidDispersionCountdown = liquidDispersionDelay;
	explosionResistance = 8;
	fireResistance = 100;
}

acid::~acid()
{
}

void acid::Darken()
{

}
