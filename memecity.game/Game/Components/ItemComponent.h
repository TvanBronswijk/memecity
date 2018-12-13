#ifndef _ITEMCOMPONENT_H
#define  _ITEMCOMPONENT_H
#include <ECS.h>
#include <iostream>
#include <Engine\MultimediaManager.h>

struct ItemComponent : public memecity::engine::ecs::Component
{
	std::string name, description;

	ItemComponent(memecity::engine::ecs::Entity& entity, std::string name, std::string description) 
		: memecity::engine::ecs::Component(entity), name{ name }, description{ description }{};
};

#endif;
