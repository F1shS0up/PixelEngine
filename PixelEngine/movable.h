#pragma once
#include "solid.h"

struct movable : public solid
{
	glm::vec2 velocity;
	glm::vec2 positionHold;
	float gravity;
	float conserveEnergyMultiplier;
	float conserveEnergyLimit;
	float friction;
	float bounciness;
	float inertialResistance;

	virtual void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y) override;
	void MoveElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew);
	void FlipElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew);
	void MoveOnXAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag);
	void MoveOnYAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag);
	void Reset() override;
	void TransferVelocity(glm::vec2 velocity) override;

	void ApplyFrictionX(double* deltaTime);
	void ApplyFrictionY(double* deltaTime);
	void VerticalContact(double* deltaTime);
	void HorizontalContact(double* deltaTime);
	void SetNeighborsFalling(class pixel_simulation* pxSim, int x, int y);
};