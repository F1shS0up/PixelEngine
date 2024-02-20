#pragma once
#include "liquid.h"
struct water : public liquid
{
	water();
	~water();
	void Darken() override;
};