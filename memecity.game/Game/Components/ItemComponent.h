#ifndef _ITEMCOMPONENT_H
#define  _ITEMCOMPONENT_H
#include <ECS.h>
#include <iostream>
#include <Engine\MultimediaManager.h>

struct ItemComponent : public memecity::engine::ecs::Component
{
	std::string name, description;

	int damage, defence;

	ItemComponent(memecity::engine::ecs::Entity& entity) : ItemComponent(entity, "unkown", "no description") {};
	ItemComponent(memecity::engine::ecs::Entity& entity, std::string name, std::string description) : ItemComponent(entity, name, description, 0, 0) {};
	ItemComponent(memecity::engine::ecs::Entity& entity, std::string name, std::string description, int damage, int defence) 
		: memecity::engine::ecs::Component(entity), name{ name }, description{ description }, damage{ damage }, defence{defence}{};
};

#endif;
