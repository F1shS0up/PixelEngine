#include "gas.h"
#include "element.h"
#include "pixel_simulation.h"
#include "immovable.h"

void gas::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{
	element::Update(deltaTime, pxSim, x, y);
	velocity += glm::vec2(0, -gravity * *deltaTime);
	positionHold += glm::vec2(velocity.x * *deltaTime, velocity.y * *deltaTime);
	int xSteps = std::floor(std::abs(positionHold.x));
	int ySteps = std::floor(std::abs(positionHold.y));
	glm::vec2 velocityDir = glm::vec2(velocity.x > 0 ? 1 : -1, velocity.y > 0 ? 1 : -1);

	positionHold = glm::vec2(positionHold.x - (velocity.x > 0 ? xSteps : -xSteps), positionHold.y - (velocity.y > 0 ? ySteps : -ySteps));

	gasDispersionCountdown -= *deltaTime;

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
				if (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density > density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					velocity *= 1 - (density / pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density);
					pxSim->FlipElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
					break;
				}
				{
					bool xMoved = upcomingPositionedX - x != 0;
					bool yMoved = upcomingPositionedY - y != 0;
					if (yMoved)
					{
						int incr = rand() % 3 - 1;
						if (pxSim->InBounds(upcomingPositionedX + incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX + incr, upcomingPositionedY);
						}
						else if (pxSim->InBounds(upcomingPositionedX - incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX - incr, upcomingPositionedY);
						}
						else if (pxSim->InBounds(x + (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x + (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
						}
						else if (pxSim->InBounds(x - (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x - (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
							gasDispersionDir = std::abs(gasDispersionDir - 1);
						}
						else
						{
							falling = false;
							velocity.y = 0;
							break;
						}
					}
					else if (xMoved)
					{
						int incr = rand() % 3 - 1;
						if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY + incr) && pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY + incr);
						}
						else if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY - incr) && pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY - incr);
						}
						else if (pxSim->InBounds(x + (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x + (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
						}
						else if (pxSim->InBounds(x - (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x - (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
							gasDispersionDir = std::abs(gasDispersionDir - 1);
						}
						else
						{
							falling = false;
							velocity.x = 0;
							break;
						}
					}
				}
			}
			else
			{
				falling = true;
				pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
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
				if (pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density > density && !dynamic_cast<immovable*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					velocity *= 1 - (density / pxSim->grid[upcomingPositionedY][upcomingPositionedX]->density);
					pxSim->FlipElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
					break;
				}
				else
				{
					bool xMoved = upcomingPositionedX - x != 0;
					bool yMoved = upcomingPositionedY - y != 0;
					if (yMoved)
					{
						int incr = rand() % 3 - 1;
						if (pxSim->InBounds(upcomingPositionedX + incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX + incr] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX + incr, upcomingPositionedY);
						}
						else if (pxSim->InBounds(upcomingPositionedX - incr, upcomingPositionedY) && pxSim->grid[upcomingPositionedY][upcomingPositionedX - incr] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX - incr, upcomingPositionedY);
						}
						else if (pxSim->InBounds(x + (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x + (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
						}
						else if (pxSim->InBounds(x - (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x - (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
							gasDispersionDir = std::abs(gasDispersionDir - 1);
						}
						else
						{
							falling = false;
							velocity.y = 0;
							break;
						}
					}
					else if (xMoved)
					{
						int incr = rand() % 3 - 1;
						if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY + incr) && pxSim->grid[upcomingPositionedY + incr][upcomingPositionedX] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY + incr);
						}
						else if (pxSim->InBounds(upcomingPositionedX, upcomingPositionedY - incr) && pxSim->grid[upcomingPositionedY - incr][upcomingPositionedX] == nullptr)
						{
							falling = true;
							pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY - incr);
						}
						else if (pxSim->InBounds(x + (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x + (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
						}
						else if (pxSim->InBounds(x - (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x - (gasDispersionDir == false ? -1 : 1)] == nullptr)
						{
							falling = false;
							gasDispersionDir = std::abs(gasDispersionDir - 1);
						}
						else
						{
							falling = false;
							velocity.x = 0;
							break;
						}
					}
				}
			}
			else
			{
				falling = true;
				pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
			}
		}
	}

	if (!falling && (!pxSim->InBounds(x, y - 1) || (pxSim->InBounds(x, y - 1) && pxSim->grid[y - 1][x] != nullptr && !pxSim->grid[y - 1][x]->falling)) && gasDispersionCountdown <= 0)
	{
		gasDispersionCountdown = gasDispersionDelay;
		if (pxSim->InBounds(x + (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x + (gasDispersionDir == false ? -1 : 1)] == nullptr)
		{
			pxSim->MoveElement(&x, &y, x + (gasDispersionDir == false ? -1 : 1), y);
		}
		else if (pxSim->InBounds(x - (gasDispersionDir == false ? -1 : 1), y) && pxSim->grid[y][x - (gasDispersionDir == false ? -1 : 1)] == nullptr)
		{
			gasDispersionDir = std::abs(gasDispersionDir - 1);
			pxSim->MoveElement(&x, &y, x + (gasDispersionDir == false ? -1 : 1), y);
		}
	}
	
}

void gas::Reset()
{
	velocity = glm::vec2(0, 0);
	positionHold = glm::vec2(0, 0);
	gasDispersionCountdown = gasDispersionDelay;
}

void gas::TransferVelocity(glm::vec2)
{
	this->velocity += velocity;
}
