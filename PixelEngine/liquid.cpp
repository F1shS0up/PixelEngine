#include "liquid.h"
#include "pixel_simulation.h"
#include <iostream>
#include <algorithm>
#include "immovable.h"
#include "movable.h"

inline float RandomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

void liquid::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{
	element::Update(deltaTime, pxSim, x, y);
	viscosityCountdown -= *deltaTime;

	if (!falling)
	{
		int incr = rand() % 2 == 1 ? 1 : -1;

		if (pxSim->InBounds(x, y + 1) && pxSim->grid[y + 1][x] != nullptr && !pxSim->grid[y + 1][x]->updated)
		{
			pxSim->grid[y + 1][x]->Update(deltaTime, pxSim, x, y + 1);
		}
		if (pxSim->InBounds(x + 1, y + 1) && pxSim->grid[y + 1][x + 1] != nullptr && !pxSim->grid[y + 1][x + 1]->updated)
		{
			pxSim->grid[y + 1][x + 1]->Update(deltaTime, pxSim, x + 1, y + 1);
		}
		if (pxSim->InBounds(x - 1, y + 1) && pxSim->grid[y + 1][x - 1] != nullptr && !pxSim->grid[y + 1][x - 1]->updated)
		{
			pxSim->grid[y + 1][x - 1]->Update(deltaTime, pxSim, x - 1, y + 1);
		}
		if (pxSim->InBounds(x + 1, y) && pxSim->grid[y][x + 1] != nullptr && !pxSim->grid[y][x + 1]->updated)
		{
			pxSim->grid[y][x + 1]->Update(deltaTime, pxSim, x + 1, y);
		}
		if (pxSim->InBounds(x - 1, y) && pxSim->grid[y][x - 1] != nullptr && !pxSim->grid[y][x - 1]->updated)
		{
			pxSim->grid[y][x - 1]->Update(deltaTime, pxSim, x - 1, y);
		}

		if (pxSim->InBounds(x, y + 1) && pxSim->grid[y + 1][x] == nullptr)
		{
			velocity = glm::vec2(0, 0);
			falling = true;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x + incr, y + 1) && pxSim->grid[y + 1][x + incr] == nullptr)
		{
			viscosityCountdown = viscosity;
			MoveElement(pxSim, x, y, x + incr, y + 1);
			return;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x - incr, y + 1) && pxSim->grid[y + 1][x - incr] == nullptr)
		{
			viscosityCountdown = viscosity;
			MoveElement(pxSim, x, y, x - incr, y + 1);
			return;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x, y + 1) && pxSim->grid[y + 1][x] != nullptr && pxSim->grid[y + 1][x]->density < density)
		{
			viscosityCountdown = viscosity + ((liquid*)pxSim->grid[y + 1][x])->viscosity;
			FlipElement(pxSim, x, y, x, y + 1);
			falling = true;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x + incr, y + 1) && pxSim->grid[y + 1][x + incr] != nullptr && pxSim->grid[y + 1][x + incr]->density < density)
		{
			viscosityCountdown = viscosity + ((liquid*)pxSim->grid[y + 1][x + incr])->viscosity;
			FlipElement(pxSim, x, y, x + incr, y + 1);
			return;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x - incr, y + 1) && pxSim->grid[y + 1][x - incr] != nullptr && pxSim->grid[y + 1][x - incr]->density < density)
		{
			viscosityCountdown = viscosity + ((liquid*)pxSim->grid[y + 1][x - incr])->viscosity;
			FlipElement(pxSim, x, y, x - incr, y + 1);
			return;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x + liquidDispersionDir, y) && pxSim->grid[y][x + liquidDispersionDir] == nullptr)
		{
			viscosityCountdown = viscosity;
			MoveElement(pxSim, x, y, x + liquidDispersionDir, y);
			return;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x - liquidDispersionDir, y) && pxSim->grid[y][x - liquidDispersionDir] == nullptr)
		{
			viscosityCountdown = viscosity;
			MoveElement(pxSim, x, y, x - liquidDispersionDir, y);
			liquidDispersionDir = -liquidDispersionDir;
			return;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x + liquidDispersionDir, y) && pxSim->grid[y][x + liquidDispersionDir] != nullptr && pxSim->grid[y][x + liquidDispersionDir]->density < density)
		{
			viscosityCountdown = viscosity + ((liquid*)pxSim->grid[y][x + liquidDispersionDir])->viscosity;
			FlipElement(pxSim, x, y, x + liquidDispersionDir, y);
			return;
		}
		else if (viscosityCountdown <= 0 && pxSim->InBounds(x - liquidDispersionDir, y) && pxSim->grid[y][x - liquidDispersionDir] != nullptr && pxSim->grid[y][x - liquidDispersionDir]->density < density)
		{
			viscosityCountdown = viscosity + ((liquid*)pxSim->grid[y][x - liquidDispersionDir])->viscosity;
			FlipElement(pxSim, x, y, x - liquidDispersionDir, y);
			liquidDispersionDir = -liquidDispersionDir;
			return;
		}
		else
		{
			liquidDispersionDir = -liquidDispersionDir;
			if (onFire)CoolDownCheck(pxSim, x, y);
			return;
		}
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
					HorizontalContact();
				}
				else if (upcomingPositionedY < 0 || upcomingPositionedY >= pxSim->HEIGHT)
				{
					VerticalContact();
					liquidDispersionDir = rand() % 2 == 1 ? 1 : -1;
				}
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
					falling = false;
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
			else
			{
				falling = true;
				MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
			}
		}
	}
	else if (xSteps != 0 || ySteps != 0)
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
					HorizontalContact();
				}
				else if (upcomingPositionedY < 0 || upcomingPositionedY >= pxSim->HEIGHT)
				{
					VerticalContact();
					liquidDispersionDir = rand() % 2 == 1 ? 1 : -1;
				}
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
					falling = false;
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
			else
			{
				falling = true;
				MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
			}
		}
	}
}

void liquid::MoveElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew)
{
	if (pxSim->grid[yNew][xNew] != nullptr) return;
	pxSim->MoveElement(&x, &y, xNew, yNew);
	if (onFire)CoolDownCheck(pxSim, x, y);
	SetNeighborsFalling(pxSim, x, y);
}
void liquid::FlipElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew)
{
	if (onFire)CoolDownCheck(pxSim, x, y);
	SetNeighborsFalling(pxSim, x, y);
	pxSim->FlipElement(&x, &y, xNew, yNew);
	if (onFire)CoolDownCheck(pxSim, x, y);
	SetNeighborsFalling(pxSim, x, y);
}

void liquid::VerticalContact()
{
	velocity.y = 0;
	falling = false;
}
void liquid::HorizontalContact()
{
	velocity.x = 0;
	falling = false;
}

void liquid::MoveOnXAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag)
{
	retFlag = 1;
	int incr = rand() % 2 == 1 ? 1 : -1;

	if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY + incr) && pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] != nullptr && !pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX]->updated)
	{
		pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX]->Update(deltaTime, pxSim, upcomingPositionedX, upcomingPositionedY + incr);
	}
	if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY - incr) && pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] != nullptr && !pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX]->updated)
	{
		pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX]->Update(deltaTime, pxSim, upcomingPositionedX, upcomingPositionedY - incr);
	}

	if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY + incr) && pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY + incr);
	}
	else if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY - incr) && pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY - incr);
	}
	else
	{
		HorizontalContact();
		{ retFlag = 2; return; };
	}
}
void liquid::MoveOnYAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, double* deltaTime, int& retFlag)
{
	retFlag = 1;
	int incr = rand() % 2 == 1 ? 1 : -1;

	if (pxSim->InBounds(upcomingPositionedX + incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] != nullptr && !pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr]->updated)
	{
		pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr]->Update(deltaTime, pxSim, upcomingPositionedX + incr, upcomingPositionedY);
	}
	if (pxSim->InBounds(upcomingPositionedX - incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] != nullptr && !pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr]->updated)
	{
		pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr]->Update(deltaTime, pxSim, upcomingPositionedX - incr, upcomingPositionedY);
	}

	if (pxSim->InBounds(upcomingPositionedX + incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX + incr, upcomingPositionedY);
	}
	else if (pxSim->InBounds(upcomingPositionedX - incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX - incr, upcomingPositionedY);
	}
	else
	{
		VerticalContact();
		liquidDispersionDir = rand() % 2 == 1 ? 1 : -1;
		{ retFlag = 2; return; };
	}
}

void liquid::Reset()
{
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	viscosityCountdown = viscosity;
}

void liquid::TransferVelocity(glm::vec2)
{
	this->velocity += velocity;
}

void liquid::SetNeighborsFalling(pixel_simulation* pxSim, int x, int y)
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
