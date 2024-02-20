#pragma once
#include "immovable.h"
struct rock : public immovable
{
	rock();
	~rock();
	void Darken() override;
};