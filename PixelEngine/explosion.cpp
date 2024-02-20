#include "explosion.h"
#include "pixel_simulation.h"
#include <iostream>
#include "solid.h"
#include "element.h"
#include <algorithm>
#include "spark.h"
#include "wood.h"
#include "smoke.h"

inline int ReverseNumber(int num, int min, int max)
{
	return (max + min) - num;
}

void explosion::ApplyExplosion(pixel_simulation* pxSim)
{
	std::vector<glm::ivec2> finalPoints;
	LoopThroughCirclePixels(radius, pxSim);

	for (int yp = -sparkRadius; yp <= sparkRadius; yp++)
	{
		for (int xp = -sparkRadius; xp <= sparkRadius; xp++)
		{
			if (xp * xp + yp * yp <= sparkRadius * sparkRadius)
			{
				if (rand() % 101 < sparkSpawnChance)
				{
					spark* s = (spark*)pxSim->CreateElement<spark>(xp + midx, yp + midy);
					s->ReplaceAsParticle(glm::vec2(
						((float)xp) / (float)sparkRadius,
						((float)yp) / (float)sparkRadius) * (sparkStrength + ((rand() % (int)sparkStrength) - sparkStrength / 2)), pxSim, xp + midx, yp + midy);
				}
			}
		}
	}
	for (int yp = -smokeRadius; yp <= smokeRadius; yp++)
	{
		for (int xp = -smokeRadius; xp <= smokeRadius; xp++)
		{
			if (xp * xp + yp * yp <= smokeRadius * smokeRadius)
			{
				if (rand() % 101 < smokeSpawnChance)
				{
					smoke* s = (smoke*)pxSim->CreateElement<smoke>(xp + midx, yp + midy);
					if (s != nullptr)s->velocity = glm::vec2(
						((float)xp) / (float)smokeRadius,
						((float)yp) / (float)smokeRadius) * (smokeStrength + ((rand() % (int)smokeStrength) - smokeStrength / 2));
				}
			}
		}
	}

	delete this;
}

void explosion::LoopThroughCirclePixels(int r, pixel_simulation* pxSim)
{
	std::vector<element*> elementsAlreadyDamaged;

	int x = 0, y = r;
	int d = 3 - 2 * r;
	CheckAllElementsFromPointToPoint(0, 0, pxSim, &elementsAlreadyDamaged);
	glm::ivec2* points = GetTheCirclePixel8(x, y);
	for (int i = 0; i < 8; i++)
	{
		CheckAllElementsFromPointToPoint(points[i].x, points[i].y, pxSim, &elementsAlreadyDamaged);
	}
	while (y >= x)
	{
		// for each pixel we will 
		// draw all eight pixels 

		x++;

		// check for decision parameter 
		// and correspondingly  
		// update d, x, y 
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		glm::ivec2* points = GetTheCirclePixel8(x, y);
		for (int i = 0; i < 8; i++)
		{
			CheckAllElementsFromPointToPoint(points[i].x, points[i].y, pxSim, &elementsAlreadyDamaged);
		}
	}
}

glm::ivec2* explosion::GetTheCirclePixel8(int x, int y)
{
	return new glm::ivec2[8]{
		glm::ivec2(+x, +y),
		glm::ivec2(-x, +y),
		glm::ivec2(+x, -y),
		glm::ivec2(-x, -y),
		glm::ivec2(+y, +x),
		glm::ivec2(-y, +x),
		glm::ivec2(+y, -x),
		glm::ivec2(-y, -x) };
}

void explosion::CheckAllElementsFromPointToPoint(int px, int py, pixel_simulation* pxSim, std::vector<element*>* elementsAlreadyDamaged)
{

	if (px == 0 && py == 0)
	{
		ApplyDamage(pxSim, midx, midy, damage, elementsAlreadyDamaged);
		return;
	}
	int xSteps = std::abs(px);
	int ySteps = std::abs(py);

	int dirX = px > 0 ? 1 : -1;
	int dirY = py > 0 ? 1 : -1;

	if (xSteps > ySteps)
	{
		float yStep = (float)ySteps / (float)xSteps;
		for (int xStep = 1; xStep <= xSteps; xStep++)
		{
			int upcomingPositionedY = (float)yStep * dirY * xStep + 0.5f + midy;
			int upcomingPositionedX = (float)dirX * xStep + midx;

			if (!pxSim->InBounds(upcomingPositionedX, upcomingPositionedY)) break;

			if (std::find(elementsAlreadyDamaged->begin(), elementsAlreadyDamaged->end(), pxSim->grid[upcomingPositionedY][upcomingPositionedX]) != elementsAlreadyDamaged->end()) continue;

			float distSqr = (upcomingPositionedX - midx) * (upcomingPositionedX - midx) + (upcomingPositionedY - midy) * (upcomingPositionedY - midy);
			float normalizedDistReversedWithRNG = ((ReverseNumber(distSqr, 0, (float)radius * (float)radius) / ((float)radius * (float)radius))) + (float)(rand() % 1001 - 500) / 2000.f;
			normalizedDistReversedWithRNG = std::clamp<float>(normalizedDistReversedWithRNG / (float)(1 - (float)fullStrengthRadius / (float)radius), 0, 1);
			float realStrength = normalizedDistReversedWithRNG * strength;
			float realDamage = normalizedDistReversedWithRNG * damage;

			if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr && pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance < realStrength)
			{
				realDamage /= std::clamp<float>((float)pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance / (float)realStrength, 1, 100);
				ApplyDamage(pxSim, upcomingPositionedX, upcomingPositionedY, realDamage, elementsAlreadyDamaged);

				if (impulseMultiplier != 0 && pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
				{
					glm::vec2 impulseDir = glm::vec2(0, 0);
					if (impulseMultiplier != 0)
					{
						impulseDir = glm::normalize(glm::vec2(upcomingPositionedX - midx + (float)(rand() % 201 - 100) / 100.f, upcomingPositionedY - midy + (float)(rand() % 201 - 100) / 100.f));
					}
					impulseDir *= impulseMultiplier;

					impulseDir /= std::clamp<float>((float)pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance / (float)realStrength, 1, 100);
					ApplyImpulse(pxSim, upcomingPositionedX, upcomingPositionedY, impulseDir);
				}
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				realDamage /= std::clamp<float>((float)pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance / (float)realStrength, 1, 100);
				ApplyDamage(pxSim, upcomingPositionedX, upcomingPositionedY, realDamage, elementsAlreadyDamaged);
				break;
			}
		}
	}
	else
	{
		float xStep = (float)xSteps / (float)ySteps;
		for (int yStep = 1; yStep <= ySteps; yStep++)
		{
			int upcomingPositionedX = (float)xStep * dirX * yStep + 0.5f + midx;
			int upcomingPositionedY = (float)dirY * yStep + midy;

			if (!pxSim->InBounds(upcomingPositionedX, upcomingPositionedY)) break;

			if (std::find(elementsAlreadyDamaged->begin(), elementsAlreadyDamaged->end(), pxSim->grid[upcomingPositionedY][upcomingPositionedX]) != elementsAlreadyDamaged->end()) continue;
			
			float distSqr = (upcomingPositionedX - midx) * (upcomingPositionedX - midx) + (upcomingPositionedY - midy) * (upcomingPositionedY - midy);
			float normalizedDistReversedWithRNG = ((ReverseNumber(distSqr, 0, (float)radius * (float)radius) / ((float)radius * (float)radius))) + (float)(rand() % 1001 - 500) / 2000.f;
			normalizedDistReversedWithRNG = std::clamp<float>(normalizedDistReversedWithRNG / (float)(1 - (float)fullStrengthRadius / (float)radius), 0, 1);
			float realStrength = normalizedDistReversedWithRNG * strength;
			float realDamage = normalizedDistReversedWithRNG * damage;

			if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr && pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance < realStrength)
			{
				realDamage /= std::clamp<float>((float)pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance / (float)realStrength, 1, 100);
				ApplyDamage(pxSim, upcomingPositionedX, upcomingPositionedY, realDamage, elementsAlreadyDamaged);

				if (impulseMultiplier != 0 && pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
				{
					glm::vec2 impulseDir = glm::vec2(0, 0);
					if (impulseMultiplier != 0)
					{
						impulseDir = glm::normalize(glm::vec2(upcomingPositionedX - midx + (float)(rand() % 201 - 100) / 100.f, upcomingPositionedY - midy + (float)(rand() % 201 - 100) / 100.f));
					}
					impulseDir *= impulseMultiplier;

					impulseDir /= std::clamp<float>((float)pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance / (float)realStrength, 1, 100);
					ApplyImpulse(pxSim, upcomingPositionedX, upcomingPositionedY, impulseDir);
				}
			}
			else if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
			{
				realDamage /= std::clamp<float>((float)pxSim->grid[upcomingPositionedY][upcomingPositionedX]->explosionResistance / (float)realStrength, 1, 100);
				ApplyDamage(pxSim, upcomingPositionedX, upcomingPositionedY, realDamage, elementsAlreadyDamaged);
				break;
			}
			
		}
	}
}

void explosion::ApplyImpulse(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, const glm::vec2& impulseDir)
{
	pxSim->grid[upcomingPositionedY][upcomingPositionedX]->ReplaceAsParticle(impulseDir, pxSim, upcomingPositionedX, upcomingPositionedY);
}

void explosion::ApplyDamage(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, float realDamage, std::vector<element*>* elementsAlreadyDamaged)
{
	if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)
	{
		elementsAlreadyDamaged->push_back(pxSim->grid[upcomingPositionedY][upcomingPositionedX]);
		pxSim->grid[upcomingPositionedY][upcomingPositionedX]->AddHealth(-realDamage - 0.1f, pxSim, upcomingPositionedX, upcomingPositionedY);
		if (pxSim->grid[upcomingPositionedY][upcomingPositionedX] != nullptr)pxSim->grid[upcomingPositionedY][upcomingPositionedX]->Darken();
	}
}


