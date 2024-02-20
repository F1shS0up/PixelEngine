#pragma once
#include "movable.h"

struct sand : public movable
{
	sand();
	~sand();
	void Darken() override;
};