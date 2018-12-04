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

	std::unique_ptr<memecity::engine::texture::TextTexture> texture;

	AIComponent(memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::TextTexture> texture) : AIComponent(entity, State::Idle, "unknown" , std::move(texture)) {};

	AIComponent(memecity::engine::ecs::Entity& entity, State type, std::string name , std::unique_ptr<memecity::engine::texture::TextTexture> texture) : memecity::engine::ecs::Component(entity), state(type), name(name) , texture(std::move(texture)) {};

	memecity::engine::texture::TextTexture& get_texture()
	{
		return *texture;
	}
};

#endif
