#include "entity.h"

std::size_t entity_manager::CreateEntity()
{
	++num_entities;
	return num_entities;
}

void entity_manager::DestroyEntity(std::size_t entity)
{
	--num_entities;
}