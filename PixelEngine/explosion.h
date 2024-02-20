#pragma once
#include "SDL.h"
#include "glm/glm.hpp"
#include <vector>

struct explosion
{
	int radius;
	int fullStrengthRadius;
	float strength;
	float damage;
	float impulseMultiplier;
	int midx, midy;

	int smokeRadius;
	int smokeSpawnChance;
	float smokeStrength;

	int sparkRadius;
	int sparkSpawnChance;
	float sparkStrength;

	void ApplyExplosion(class pixel_simulation* pxSim);
	void LoopThroughCirclePixels(int r, class pixel_simulation* pxSim);
	glm::ivec2* GetTheCirclePixel8(int x, int y);
	void CheckAllElementsFromPointToPoint(int px, int py, class pixel_simulation* pxSim, std::vector<class element*>* elementsAlreadyDamaged);
	void ApplyImpulse(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, const glm::vec2& impulseDir);
	void ApplyDamage(pixel_simulation* pxSim, int upcomingPositionedX, int upcomingPositionedY, float realDamage, std::vector<class element*>* elementsAlreadyDamaged);
};