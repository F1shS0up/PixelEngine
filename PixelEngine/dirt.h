#pragma once
#include "movable.h"

struct dirt : public movable
{
	dirt();
	~dirt();
	void Darken() override;
};
