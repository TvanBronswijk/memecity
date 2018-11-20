#ifndef _INTERACTIONCOMPONENT_H
#define  _INTERACTIONCOMPONENT_H
#include <ECS.h>
#include <vector>
#include <Engine\MultimediaManager.h>
#include "DrawableComponent.h"

struct InteractionComponent : public memecity::engine::ecs::Component{


public:
	size_t timer = 0;
	std::vector<std::string> smallTalk; // markovketen
	std::unique_ptr<memecity::engine::texture::Texture> texture;

	InteractionComponent(const memecity::engine::ecs::Entity& entity, memecity::engine::MultimediaManager& multimedia_manager) : InteractionComponent(entity, { "Hello Stranger!", "Sorry, i can't talk now.", "what are you doing?" } , multimedia_manager) {};
	InteractionComponent(const memecity::engine::ecs::Entity& entity, std::vector<std::string> smallTalk, memecity::engine::MultimediaManager& multimedia_manager) : memecity::engine::ecs::Component(entity), smallTalk(smallTalk) { set_texture(multimedia_manager); };

	memecity::engine::texture::Texture& get_texture()
	{
		return *texture;
	}
	void set_texture(memecity::engine::MultimediaManager& multimedia_manager) {
		auto parent = entity.get<DrawableComponent>();

		auto npc_interaciton_texture = multimedia_manager.get_text_texture(" ", "Minecraftia-Regular.ttf", 14, { 255,255,255 });
		npc_interaciton_texture->set_position({ 0, -35 });
		npc_interaciton_texture->set_parent(&parent->get_texture());
		texture = std::move(npc_interaciton_texture);
	}

	void increment_timer() {
		timer++;
	}
	void reset_timer() {
		timer = 0;
	}
	size_t get_timer() {
		return timer;
	}
};

#endif
