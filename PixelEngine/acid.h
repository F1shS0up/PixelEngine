#pragma once
#include "liquid.h"
struct acid : public liquid
{
	acid();
	~acid();
	void Darken() override;
};
