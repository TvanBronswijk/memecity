#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include <ECS.h>
#include <vector>
#include <ctime>
#include <Engine\MultimediaManager.h>

struct InteractionComponent : public memecity::engine::ecs::Component{
public:
	float start_time = 0;
	int current_text_int = 0;

	std::vector<std::string> text; // markovketen
	std::unique_ptr<memecity::engine::texture::TextTexture> texture;
	InteractionComponent(memecity::engine::ecs::Entity& entity) : 
		InteractionComponent(entity, nullptr) {};
	InteractionComponent(memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::TextTexture> texture) :
		InteractionComponent(entity, {" "}, std::move(texture)) {};
	InteractionComponent(memecity::engine::ecs::Entity& entity, std::vector<std::string> text, std::unique_ptr<memecity::engine::texture::TextTexture> texture) 
		: memecity::engine::ecs::Component(entity), text(text), texture(std::move(texture)) {};

	memecity::engine::texture::TextTexture& get_texture()
	{
		return *texture;
	}
};

#endif
