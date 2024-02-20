#pragma once
#include "movable.h"

struct rubber : public movable
{
	rubber();
	~rubber();
	void Darken() override;
};
