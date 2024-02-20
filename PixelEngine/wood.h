#pragma once
#include "immovable.h"
struct wood : public immovable
{
	wood();
	~wood();
	void Darken() override;
};