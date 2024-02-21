#pragma once
#include "element.h"
struct liquid : public element
{
	glm::vec2 velocity;
	glm::vec2 positionHold;
	float gravity;
	float viscosity;
	float viscosityCountdown;
	int liquidDispersionDir;

	void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y) override;
	void MoveElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew);
	void FlipElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew);
	void VerticalContact();
	void HorizontalContact();
	void MoveOnYAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag);
	void MoveOnXAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag);
	void Reset() override;
	void TransferVelocity(glm::vec2 velocity) override;
	void SetNeighborsFalling(pixel_simulation* pxSim, int x, int y);
};
