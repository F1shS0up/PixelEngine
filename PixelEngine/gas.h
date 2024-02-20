#pragma once
#pragma once
#include "element.h"
struct gas : public element
{
	glm::vec2 velocity;
	glm::vec2 positionHold;
	float gravity;
	float gasDispersionDelay;
	float gasDispersionCountdown;
	bool gasDispersionDir;

	void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y) override;
	void Reset() override;
	void TransferVelocity(glm::vec2 velocity) override;
};