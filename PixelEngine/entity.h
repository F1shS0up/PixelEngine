#pragma once
#include <iostream>

using entity = std::size_t;
const entity max_entity = 5000;

class entity_manager
{
public:
	entity num_entities = 0;

	std::size_t CreateEntity();
	void DestroyEntity(std::size_t entity);

};