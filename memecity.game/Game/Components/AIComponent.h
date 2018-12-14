#ifndef _AICOMPONENT_H
#define  _AICOMPONENT_H
#include <ECS.h>
#include <iostream>
#include "../Enum/AIStates.h"

struct AIComponent : public memecity::engine::ecs::Component {
	
	enum class Direction { Left, Right, Down, Up, Idle };
	State state;
	Direction direction;
	std::string name;
	float timer_fighting;
	float movement_speed;
	int exp;
	int range_of_fighting;

	std::unique_ptr<memecity::engine::texture::TextTexture> texture;

	AIComponent(memecity::engine::ecs::Entity& entity, State type, std::string name,int exp,int range_of_fighting, float movement_speed, std::unique_ptr<memecity::engine::texture::TextTexture> texture) : 
		memecity::engine::ecs::Component(entity), state(type), name(name) , movement_speed(movement_speed),  texture(std::move(texture)),exp(exp), timer_fighting(0), range_of_fighting(range_of_fighting) {};

	memecity::engine::texture::TextTexture& get_texture()
	{
		return *texture;
	}
};

#endif
