#pragma once
#include "liquid.h"
struct oil : public liquid
{
	oil();
	~oil();
	void Darken() override;
};
