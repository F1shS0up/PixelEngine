#pragma once
#include "gas.h"
struct steam : public gas
{
	steam();
	~steam();
	void Darken() override;
};