#include "movable.h"
#include "pixel_simulation.h"
#include <iostream>
#include <algorithm>
#include "liquid.h"

inline float RandomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

void movable::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{

	if (!falling)
	{
		if (onFire)CoolDownCheck(pxSim, x, y);
		velocity = glm::vec2(0, 0);
		if (pxSim->InBounds(x, y + 1) && (pxSim->grid[y + 1][x] == nullptr || (pxSim->grid[y + 1][x] != nullptr && !dynamic_cast<solid*>(pxSim->grid[y + 1][x]) && pxSim->grid[y + 1][x]->density < density)))
		{
			falling = true;
		}
		element::Update(deltaTime, pxSim, x, y);
		return;
	}

	velocity += glm::vec2(0, gravity * *deltaTime);
	positionHold += glm::vec2(velocity.x * *deltaTime, velocity.y * *deltaTime);
	int xSteps = std::floor(std::abs(positionHold.x));
	int ySteps = std::floor(std::abs(positionHold.y));
	glm::vec2 velocityDir = glm::vec2(velocity.x > 0 ? 1 : -1, velocity.y > 0 ? 1 : -1);

	positionHold = glm::vec2(positionHold.x - (velocity.x > 0 ? xSteps : -xSteps), positionHold.y - (velocity.y > 0 ? ySteps : -ySteps));

	if (xSteps > ySteps)
	{
		float yStep = (float)ySteps / (float)xSteps;
		for (int xStep = 1; xStep <= xSteps; xStep++)
		{
			int upcomingPositionedY = (float)yStep * velocityDir.y + 0.5f + y;
			int upcomingPositionedX = (float)velocityDir.x + x;

			if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr && !pxSim->grid[upcomingPositionedY][upcomingPositionedX]->updated)
			{
				pxSim->grid[upcomingPositionedY][upcomingPositionedX]->Update(deltaTime, pxSim, upcomingPositionedX, upcomingPositionedY);
			}

			if (!pxSim->InBounds(upcomingPositionedX, upcomingPositionedY))
			{
				if (upcomingPositionedX < 0 || upcomingPositionedX >= pxSim->WIDTH)
				{
					HorizontalContact(deltaTime);
				}
				else if (upcomingPositionedY < 0 || upcomingPositionedY >= pxSim->HEIGHT)
				{
					VerticalContact(deltaTime);
				}
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (!dynamic_cast<solid*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]) && pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density < density)
				{
					velocity *= (1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density / density));
					FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
					falling = true;
					break;
				}
				else
				{
					bool xMoved = upcomingPositionedX - x != 0;
					bool yMoved = upcomingPositionedY - y != 0;
					if (yMoved)
					{
						int retFlag;
						MoveOnYAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, deltaTime, retFlag);
						if (retFlag == 2) break;
					}
					else if (xMoved)
					{
						int retFlag;
						MoveOnXAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, deltaTime, retFlag);
						if (retFlag == 2) break;
					}
				}
			}
			else if(pxSim->grid[upcomingPositionedY][upcomingPositionedX] == nullptr)
			{
				falling = true;
				MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
			}
		}
	}
	else
	{
		float xStep = (float)xSteps / (float)ySteps;
		for (int yStep = 1; yStep <= ySteps; yStep++)
		{
			int upcomingPositionedX = (float)xStep * velocityDir.x + 0.5f + x;
			int upcomingPositionedY = (float)velocityDir.y + y;

			if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr && !pxSim->grid[upcomingPositionedY][upcomingPositionedX]->updated)
			{ 
				pxSim->grid[upcomingPositionedY][upcomingPositionedX]->Update(deltaTime, pxSim, upcomingPositionedX, upcomingPositionedY); 
			}

			if (!pxSim->InBounds(upcomingPositionedX, upcomingPositionedY))
			{
				if (upcomingPositionedX < 0 || upcomingPositionedX >= pxSim->WIDTH)
				{
					HorizontalContact(deltaTime);
				}
				else if (upcomingPositionedY < 0 || upcomingPositionedY >= pxSim->HEIGHT)
				{
					VerticalContact(deltaTime);
				}
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (!dynamic_cast<solid*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]) && pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density < density)
				{
					velocity *= (1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density / density));
					FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
					falling = true;
					break;
				}
				else
				{
					bool xMoved = upcomingPositionedX - x != 0;
					bool yMoved = upcomingPositionedY - y != 0;
					if (yMoved)
					{
						int retFlag;
						MoveOnYAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, deltaTime, retFlag);
						if (retFlag == 2) break;
					}
					else if (xMoved)
					{
						int retFlag;
						MoveOnXAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, deltaTime, retFlag);
						if (retFlag == 2) break;
					}
				}
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] == nullptr)
			{
				falling = true;
				MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
			}
		}
	}
	if (!pxSim->InBounds(x, y + 1) || (pxSim->grid[y + 1][x] != nullptr))
	{
		ApplyFrictionX(deltaTime);
	}
	if (!pxSim->InBounds(x, y - 1) || (pxSim->grid[y - 1][x] != nullptr))
	{
		ApplyFrictionX(deltaTime);
	}

	element::Update(deltaTime, pxSim, x, y);
}

void movable::MoveElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew)
{
	pxSim->MoveElement(&x, &y, xNew, yNew);
	if (onFire)CoolDownCheck(pxSim, x, y);
	SetNeighborsFalling(pxSim, x, y);
}
void movable::FlipElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew)
{
	pxSim->FlipElement(&x, &y, xNew, yNew);
	if (onFire)CoolDownCheck(pxSim, x, y);
	SetNeighborsFalling(pxSim, x, y);
}

void movable::MoveOnXAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag)
{
	retFlag = 1;
	int incr = rand() % 2 == 0 ? -1 : 1;

	if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY + incr) && pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] != nullptr && !pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX]->updated)
	{
		pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX]->Update(deltaTime, pxSim, upcomingPositionedX, upcomingPositionedY + incr);
	}
	if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY - incr) && pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] != nullptr && !pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX]->updated)
	{
		pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX]->Update(deltaTime, pxSim, upcomingPositionedX, upcomingPositionedY - incr);
	}

	if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY + incr) && (pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] == nullptr ||
		pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] != nullptr && !dynamic_cast<solid*>(pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX]) &&
		pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX]->density < density))
	{
		if (pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] != nullptr)
		{
			velocity *= (1 - (pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX]->density / density));
			FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY + incr);
		}
		else
		{
			srand(SDL_GetTicks());
			if (RandomFloat() < inertialResistance)
			{
				falling = false;
			}
			MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY + incr);
		}
	}
	else if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY - incr) && (pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] == nullptr ||
		pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] != nullptr && !dynamic_cast<solid*>(pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX]) &&
		pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX]->density < density))
	{
		if (pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] != nullptr)
		{
			velocity *= (1 - (pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX]->density / density));
			FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY - incr);
		}
		else
		{
			srand(SDL_GetTicks());
			if (RandomFloat() < inertialResistance)
			{
				falling = false;
			}
			MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY - incr);
		}
	}
	else
	{
		HorizontalContact(deltaTime);
		{ retFlag = 2; return; };
	}
}
void movable::MoveOnYAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag)
{
	retFlag = 1;
	int incr = rand() % 2 == 0 ? -1 : 1;

	if (pxSim->InBounds(upcomingPositionedX + incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] != nullptr && !pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr]->updated)
	{
		pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr]->Update(deltaTime, pxSim, upcomingPositionedX + incr, upcomingPositionedY);
	}
	if (pxSim->InBounds(upcomingPositionedX - incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] != nullptr && !pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr]->updated)
	{
		pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr]->Update(deltaTime, pxSim, upcomingPositionedX - incr, upcomingPositionedY);
	}

	if (pxSim->InBounds(upcomingPositionedX + incr, upcomingPositionedY) && (pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] == nullptr ||
		(pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] != nullptr && !dynamic_cast<solid*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr]) &&
		pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr]->density < density)))
	{
		if (pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] != nullptr)
		{
			velocity *= (1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr]->density / density));
			FlipElement(pxSim, x, y, upcomingPositionedX + incr, upcomingPositionedY);
		}
		else
		{
			srand(SDL_GetTicks());
			if (RandomFloat() < inertialResistance)
			{
				falling = false;
			}
			MoveElement(pxSim, x, y, upcomingPositionedX + incr, upcomingPositionedY);
		}
	}
	else if (pxSim->InBounds(upcomingPositionedX - incr, upcomingPositionedY) && (pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] == nullptr ||
		(pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] != nullptr && !dynamic_cast<solid*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr]) &&
		pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr]->density < density)))
	{
		if (pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] != nullptr)
		{
			velocity *= (1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr]->density / density));
			FlipElement(pxSim, x, y, upcomingPositionedX - incr, upcomingPositionedY);
		}
		else
		{
			srand(SDL_GetTicks());
			if (RandomFloat() < inertialResistance)
			{
				falling = false;
			}
			MoveElement(pxSim, x, y, upcomingPositionedX - incr, upcomingPositionedY);
		}
	}
	else
	{
		VerticalContact(deltaTime);
		{ retFlag = 2; return; };
	}
}

void movable::Reset()
{
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
}

void movable::TransferVelocity(glm::vec2 velocity)
{
	this->velocity += velocity;
}

void movable::ApplyFrictionX(double* deltaTime)
{
	if (velocity.x > 0)
	{
		velocity.x -= std::clamp<float>(friction * *deltaTime, 0, velocity.x);
	}
	else
	{
		velocity.x += std::clamp<float>(friction * *deltaTime, 0, -velocity.x);
	}
}
void movable::ApplyFrictionY(double* deltaTime)
{
	if (velocity.y > 0)
	{
		velocity.y -= std::clamp<float>(friction / 2 * *deltaTime, 0, velocity.y);
	}
	else
	{
		velocity.y += std::clamp<float>(friction / 2 * *deltaTime, 0, -velocity.y);
	}
}

void movable::VerticalContact(double* deltaTime)
{
	if (falling)
	{
		if (velocity.x != 0)
		{
			velocity.x = (velocity.x > 0 ? std::abs(velocity.y) * conserveEnergyMultiplier : -std::abs(velocity.y) * conserveEnergyMultiplier);
		}
		else
		{
			if (std::rand() % 2 == 0)
			{
				velocity.x = std::clamp<float>(std::abs(velocity.y) * conserveEnergyMultiplier, 0, conserveEnergyLimit);
			}
			else
			{
				velocity.x = -std::clamp<float>(std::abs(velocity.y) * conserveEnergyMultiplier, 0, conserveEnergyLimit);
			}
		}
		velocity.y *= -bounciness;
		if (velocity.y == 0) falling = false;
	}
	else
	{
		falling = false;
	}
	ApplyFrictionX(deltaTime);
}
void movable::HorizontalContact(double* deltaTime)
{
	if (falling)
	{
		if (velocity.y != 0)
		{
			velocity.y = (velocity.y > 0 ? std::abs(velocity.x) * conserveEnergyMultiplier : -std::abs(velocity.x) * conserveEnergyMultiplier);
		}
		else
		{
			if (std::rand() % 2 == 0)
			{
				velocity.y = std::clamp<float>(std::abs(velocity.x) * conserveEnergyMultiplier, 0, conserveEnergyLimit);
			}
			else
			{
				velocity.y = -std::clamp<float>(std::abs(velocity.x) * conserveEnergyMultiplier, 0, conserveEnergyLimit);
			}
		}
		velocity.x *= -bounciness;
		if (velocity.x == 0) falling = false;
	}
	else
	{
		falling = false;
	}
	ApplyFrictionY(deltaTime);
}

void movable::SetNeighborsFalling(pixel_simulation* pxSim, int x, int y)
{
	if (pxSim->InBounds(x + 1, y))
	{
		if (dynamic_cast<movable*>(pxSim->grid[y][x + 1]))
		{
			srand(SDL_GetTicks());
			if (RandomFloat() >= ((movable*)pxSim->grid[y][x + 1])->inertialResistance)
			{
				pxSim->grid[y][x + 1]->falling = true;
			}
		}
	}
	if (pxSim->InBounds(x - 1, y))
	{
		if (dynamic_cast<movable*>(pxSim->grid[y][x - 1]))
		{
			srand(SDL_GetTicks());
			if (RandomFloat() >= ((movable*)pxSim->grid[y][x - 1])->inertialResistance)
			{
				pxSim->grid[y][x - 1]->falling = true;
			}
		}
	}
	if (pxSim->InBounds(x, y + 1))
	{
		if (dynamic_cast<movable*>(pxSim->grid[y + 1][x]))
		{
			srand(SDL_GetTicks());
			if (RandomFloat() >= ((movable*)pxSim->grid[y + 1][x])->inertialResistance)
			{
				pxSim->grid[y + 1][x]->falling = true;
			}
		}
	}
	if (pxSim->InBounds(x, y - 1))
	{
		if (dynamic_cast<movable*>(pxSim->grid[y - 1][x]))
		{
			srand(SDL_GetTicks());
			if (RandomFloat() >= ((movable*)pxSim->grid[y - 1][x])->inertialResistance)
			{
				pxSim->grid[y - 1][x]->falling = true;
			}
		}
	}
}

