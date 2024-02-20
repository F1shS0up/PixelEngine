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
	liquidDispersionCountdown -= *deltaTime;

	if (!falling)
	{
		velocity += glm::vec2(0, gravity * *deltaTime);
		positionHold += glm::vec2(velocity.x * *deltaTime, velocity.y * *deltaTime);
		int xSteps = std::floor(std::abs(positionHold.x));
		int ySteps = std::floor(std::abs(positionHold.y));

		positionHold = glm::vec2(positionHold.x - (velocity.x > 0 ? xSteps : -xSteps), positionHold.y - (velocity.y > 0 ? ySteps : -ySteps));

		if (pxSim->InBounds(x, y + 1) && pxSim->grid[y + 1][x] == nullptr)
		{
			velocity = glm::vec2(0, 0);
			falling = true;
		}
		else if (pxSim->InBounds(x + 1, y + 1) && pxSim->grid[y + 1][x + 1] == nullptr)
		{
			velocity = glm::vec2(0, 0);
			falling = true;
		}
		else if (pxSim->InBounds(x - 1, y + 1) && pxSim->grid[y + 1][x - 1] == nullptr)
		{
			velocity = glm::vec2(0, 0);
			falling = true;
		}
		else if (ySteps != 0 && pxSim->InBounds(x, y + ySteps) && pxSim->grid[y + ySteps][x] != nullptr && pxSim->grid[y + ySteps][x]->density < density && !dynamic_cast<immovable*>(pxSim->grid[y + ySteps][x]))
		{
			velocity *= 1 - (pxSim->grid[y + ySteps][x]->density / density);
			FlipElement(pxSim, x, y, x, y + ySteps);
			return;
		}
		else if (ySteps != 0 && pxSim->InBounds(x + 1, y + ySteps) && pxSim->grid[y + ySteps][x + 1] != nullptr && pxSim->grid[y + ySteps][x + 1]->density < density && !dynamic_cast<immovable*>(pxSim->grid[y + ySteps][x + 1]))
		{
			velocity *= 1 - (pxSim->grid[y + ySteps][x + 1]->density / density);
			FlipElement(pxSim, x, y, x + 1, y + ySteps);
			return;
		}
		else if (ySteps != 0 && pxSim->InBounds(x - 1, y + ySteps) && pxSim->grid[y + ySteps][x - 1] != nullptr && pxSim->grid[y + ySteps][x - 1]->density < density && !dynamic_cast<immovable*>(pxSim->grid[y + ySteps][x - 1]))
		{
			velocity *= 1 - (pxSim->grid[y + ySteps][x - 1]->density / density);
			FlipElement(pxSim, x, y, x - 1, y + ySteps);
			return;
		}
		else if ((!pxSim->InBounds(x, y + 1) || (pxSim->InBounds(x, y + 1) && pxSim->grid[y + 1][x] != nullptr)) && liquidDispersionCountdown <= 0)
		{
			if (pxSim->InBounds(x + (liquidDispersionDir == false ? -1 : 1), y) && (pxSim->grid[y][x + (liquidDispersionDir == false ? -1 : 1)] == nullptr))
			{
				liquidDispersionCountdown = liquidDispersionDelay;
				MoveElement(pxSim, x, y, x + (liquidDispersionDir == false ? -1 : 1), y);
			}
			else
			{
				if (pxSim->InBounds(x + (liquidDispersionDir == false ? -1 : 1), y) && 
					dynamic_cast<liquid*>(pxSim->grid[y][x + (liquidDispersionDir == false ? -1 : 1)]) &&
					pxSim->grid[y][x + (liquidDispersionDir == false ? -1 : 1)]->density < density &&
					(!pxSim->InBounds(x, y + 1) || !dynamic_cast<liquid*>(pxSim->grid[y + 1][x]) || pxSim->grid[y + 1][x]->density >= density))
				{
					liquidDispersionCountdown = liquidDispersionDelay * 2;
					FlipElement(pxSim, x, y, x + (liquidDispersionDir == false ? -1 : 1), y);
				}
				else
				{
					liquidDispersionDir = liquidDispersionDir == false ? true : false;
				}
			}
			return;
		}
		else
		{
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

			if (!pxSim->InBounds(upcomingPositionedX, upcomingPositionedY))
			{
				falling = false;
				if (upcomingPositionedX < 0 || upcomingPositionedX >= pxSim->WIDTH)
				{
					velocity.x = 0;
				}
				else if (upcomingPositionedY < 0 || upcomingPositionedY >= pxSim->HEIGHT)
				{
					velocity.y = 0;
				}
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
				}
				else if (pxSim->InBounds(upcomingPositionedX + 1, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1] != nullptr && pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX + 1, upcomingPositionedY);
				}
				else if (pxSim->InBounds(upcomingPositionedX - 1, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1] != nullptr && pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX - 1, upcomingPositionedY);
				}
				else 
				{
					bool xMoved = upcomingPositionedX - x != 0;
					bool yMoved = upcomingPositionedY - y != 0;
					if (yMoved)
					{
						int retFlag;
						MoveOnYAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, retFlag);
						if (retFlag == 2) break;
					}
					else if (xMoved)
					{
						int retFlag;
						MoveOnXAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, retFlag);
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

			if (!pxSim->InBounds(upcomingPositionedX, upcomingPositionedY))
			{
				falling = false;
				if (upcomingPositionedX < 0 || upcomingPositionedX >= pxSim->WIDTH)
				{
					velocity.x = 0;
				}
				else if (upcomingPositionedY < 0 || upcomingPositionedY >= pxSim->HEIGHT)
				{
					velocity.y = 0;
				}
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY);
					break;
				}
				else if (pxSim->InBounds(upcomingPositionedX + 1, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1] != nullptr && pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX + 1]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX + 1, upcomingPositionedY);
				}
				else if (pxSim->InBounds(upcomingPositionedX - 1, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1] != nullptr && pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1]->density < density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1]))
				{
					velocity *= 1 - (pxSim->grid[upcomingPositionedY][upcomingPositionedX - 1]->density / density);
					FlipElement(pxSim, x, y, upcomingPositionedX - 1, upcomingPositionedY);
				}
				else
				{
					bool xMoved = upcomingPositionedX - x != 0;
					bool yMoved = upcomingPositionedY - y != 0;
					if (yMoved)
					{
						int retFlag;
						MoveOnYAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, retFlag);
						if (retFlag == 2) break;
					}
					else if (xMoved)
					{
						int retFlag;
						MoveOnXAxis(pxSim, upcomingPositionedX, upcomingPositionedY, x, y, retFlag);
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
	pxSim->MoveElement(&x, &y, xNew, yNew);
	if (onFire)CoolDownCheck(pxSim, x, y);
	SetNeighborsFalling(pxSim, x, y);
}
void liquid::FlipElement(pixel_simulation* pxSim, int& x, int& y, int xNew, int yNew)
{
	pxSim->FlipElement(&x, &y, xNew, yNew);
	if (onFire)CoolDownCheck(pxSim, x, y);
	SetNeighborsFalling(pxSim, x, y);
}

void liquid::MoveOnXAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, int& retFlag)
{
	retFlag = 1;
	int incr = rand() % 2 == 1 ? 1 : -1;
	if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY + incr) && pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY + incr);
	}
	else if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY - incr) && pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX, upcomingPositionedY - incr);
	}
	else if (pxSim->InBounds(x + (liquidDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x + (liquidDispersionDir == false ? -1 : 1)] == nullptr)
	{
		falling = false;
	}
	else if (pxSim->InBounds(x - (liquidDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x - (liquidDispersionDir == false ? -1 : 1)] == nullptr)
	{
		falling = false;
		liquidDispersionDir = !liquidDispersionDir;
	}
	else
	{
		falling = false;
		velocity.x = 0;
		{ retFlag = 2; return; };
	}
}
void liquid::MoveOnYAxis(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, int& x, int& y, int& retFlag)
{
	retFlag = 1;
	int incr = rand() % 2 == 1 ? 1 : -1;
	if (pxSim->InBounds(upcomingPositionedX + incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX + incr, upcomingPositionedY);
	}
	else if (pxSim->InBounds(upcomingPositionedX - incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] == nullptr)
	{
		MoveElement(pxSim, x, y, upcomingPositionedX - incr, upcomingPositionedY);
	}
	else if (pxSim->InBounds(x + (liquidDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x + (liquidDispersionDir == false ? -1 : 1)] == nullptr)
	{
		falling = false;
	}
	else if (pxSim->InBounds(x - (liquidDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x - (liquidDispersionDir == false ? -1 : 1)] == nullptr)
	{
		falling = false;
		liquidDispersionDir = !liquidDispersionDir;
	}
	else
	{
		falling = false;
		velocity.y = 0;
		{ retFlag = 2; return; };
	}
}

void liquid::Reset()
{
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	liquidDispersionCountdown = liquidDispersionDelay;
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
