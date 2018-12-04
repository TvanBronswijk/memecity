#include "DrawSystem.h"
#include <Engine\Textures.h>
#include "..\Components.h"

using namespace memecity::engine::ecs;

void DrawSystem::run(EntityManager& em) const
{
	auto& player = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_base = player.get<BaseComponent>();
	auto player_texture_position = player_base->get_texture().get_position();

	float half_w = multimedia_manager.get_screen_width() / 2.0f;
	float half_h = multimedia_manager.get_screen_height() / 2.0f;
	auto components = em.query<BaseComponent>()
		.where([&](BaseComponent& c) { 
		return c.location.x > player_base->location.x - half_w - 255 
			&& c.location.x < player_base->location.x + half_w + 255
			&& c.location.y > player_base->location.y - half_h - 255
			&& c.location.y < player_base->location.y + half_h + 255;
	}).to_vector();
	
	for (BaseComponent& base_component : components)
	{	
		auto& tex = base_component.get_texture();
		if (player != base_component.entity())
		{
			tex.set_position({ 
				player_texture_position.x - (player_base->location.x - base_component.location.x), 
				player_texture_position.y - (player_base->location.y - base_component.location.y) 
				});
		}
		auto text_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&tex);
		text_texture ? multimedia_manager.render_texture(*text_texture) : multimedia_manager.render_texture(tex);
	}
}
