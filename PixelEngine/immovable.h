#pragma once
#include "solid.h"
struct immovable : public solid
{
	void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y) override;
	void Reset() override;
};