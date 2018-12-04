#ifndef _QUEST_AI_COMPONENT_H
#define  _QUEST_AI_COMPONENT_H
#include <ECS.h>
#include <iostream>
#include "../Enum/AIStates.h"

struct QuestAIComponent : public memecity::engine::ecs::Component {

	State state = State::Idle;
	std::string name;

	std::unique_ptr<memecity::engine::texture::TextTexture> texture;

	QuestAIComponent(memecity::engine::ecs::Entity& entity, std::string name , std::unique_ptr<memecity::engine::texture::TextTexture> texture) : memecity::engine::ecs::Component(entity), name(name) , texture(std::move(texture)) {};

	memecity::engine::texture::TextTexture& get_texture()
	{
		return *texture;
	}
};

#endif
