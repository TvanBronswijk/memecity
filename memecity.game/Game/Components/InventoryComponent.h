#ifndef _INVENTORYCOMPONENT_H
#define  _INVENTORYCOMPONENT_H
#include <ECS.h>
#include "ItemComponent.h"
#include <vector>

struct InventoryComponent : public memecity::engine::ecs::Component
{
	std::vector<const memecity::engine::ecs::Entity*> items;

	int selected = 0;

	InventoryComponent(memecity::engine::ecs::Entity& entity) : memecity::engine::ecs::Component(entity) {};
};

#endif;
