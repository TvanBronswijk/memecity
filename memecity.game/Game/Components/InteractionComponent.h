#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include <ECS.h>
#include <vector>
#include <Engine\MultimediaManager.h>
#include "DrawableComponent.h"

struct InteractionComponent : public memecity::engine::ecs::Component{
public:
	int timer = 0;
	std::vector<std::string> smallTalk; // markovketen
	std::unique_ptr<memecity::engine::texture::TextTexture> texture;
	InteractionComponent(memecity::engine::ecs::Entity& entity) : 
		InteractionComponent(entity, nullptr) {};
	InteractionComponent(memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::TextTexture> texture) :
		InteractionComponent(entity, { "Hello Stranger!", "Sorry, i can't talk now.", "what are you doing?" }, std::move(texture)) {};
	InteractionComponent(memecity::engine::ecs::Entity& entity, std::vector<std::string> smallTalk, std::unique_ptr<memecity::engine::texture::TextTexture> texture) 
		: memecity::engine::ecs::Component(entity), smallTalk(smallTalk), texture(std::move(texture)) {};

	memecity::engine::texture::TextTexture& get_texture()
	{
		return *texture;
	}
};

#endif
