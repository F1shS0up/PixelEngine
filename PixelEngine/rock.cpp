#include "rock.h"
#include <algorithm>

rock::rock()
{
	Uint8 x = (Uint8)(rand() % 50 + 69);
	initialColor = SDL_Color{ x, x, x, 255 };
	color = initialColor;
	updated = false;
	density = 3.f;
	explosionResistance = 80;
	fireResistance = 100;
}

rock::~rock()
{

}

void rock::Darken()
{
	color = SDL_Color
	{
		(Uint8)(initialColor.r * std::clamp<float>((health + 0.5f), 0, 1)),
		(Uint8)(initialColor.g * std::clamp<float>((health + 0.5f), 0, 1)),
		(Uint8)(initialColor.b * std::clamp<float>((health + 0.5f), 0, 1)),
		(Uint8)(initialColor.a)
	};
}