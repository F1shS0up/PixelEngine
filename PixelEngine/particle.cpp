#include "particle.h"
#include "pixel_simulation.h"
#include <iostream>
#include "gas.h"

particle::particle(float gravity, element* replacementElement, SDL_Color color, glm::vec2 vel, float health, float explosionResistance) : element()
{
	this->gravity = gravity;
	this->replacementElement = replacementElement;
	this->color = color;
	this->velocity = vel;
	this->health = health;
	this->explosionResistance = explosionResistance;
	positionHold = glm::vec2(0, 0);
}

particle::~particle()
{
}

void particle::Update(double* deltaTime, pixel_simulation* pxSim, int x, int y)
{
	element::Update(deltaTime, pxSim, x, y);
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
				Contact(pxSim, x, y);
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (dynamic_cast<particle*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					((particle*)pxSim->grid[upcomingPositionedY][upcomingPositionedX])->velocity += velocity;
					Contact(pxSim, x, y);
				}
				else if (dynamic_cast<gas*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					pxSim->FlipElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
				}
				else
				{
					Contact(pxSim, x, y);
				}
				break;
			}
			else
			{
				pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
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

			if (!pxSim->InBounds(upcomingPositionedX, upcomingPositionedY))
			{
				Contact(pxSim, x, y);
				break;
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				if (dynamic_cast<particle*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					((particle*)pxSim->grid[upcomingPositionedY][upcomingPositionedX])->velocity += velocity;
					Contact(pxSim, x, y);
				}
				else if (dynamic_cast<gas*>(pxSim->grid[upcomingPositionedY][upcomingPositionedX]))
				{
					pxSim->FlipElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
				}
				else
				{
					Contact(pxSim, x, y);
				}
				break;
			}
			else
			{
				pxSim->MoveElement(&x, &y, upcomingPositionedX, upcomingPositionedY);
			}
		}
	}
}

void particle::Contact(pixel_simulation* pxSim, int x, int y)
{
	replacementElement->Reset();
	replacementElement->TransferVelocity(velocity);
	pxSim->ReplaceElementAndDeleteLast(x, y, replacementElement);
}
