#pragma once
#include "gas.h"
struct smoke : public gas
{
	smoke();
	~smoke();
	float damagePerSecond;
	void Darken() override;
	void Update(double* deltaTime, class pixel_simulation* pxSim, int x, int y) override;
};