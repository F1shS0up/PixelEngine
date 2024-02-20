#pragma once
#include "element.h"
struct particle : public element
{
	glm::vec2 velocity;
	glm::vec2 positionHold;
	float gravity;
	element* replacementElement;

	particle(float gravity, element* replacementElement, SDL_Color color, glm::vec2 vel, float health, float explosionResistance);
	~particle();

	void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y) override;
	void Contact(class pixel_simulation* pxSim, int x, int y);
};