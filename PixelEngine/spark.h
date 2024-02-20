#pragma once
#include "movable.h"

struct spark : public movable
{
	spark();
	~spark();
	void Darken() override;
	void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y) override;
};