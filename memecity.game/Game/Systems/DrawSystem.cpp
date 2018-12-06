#include "DrawSystem.h"
#include <Engine\Textures.h>
#include "../Components/VelocityComponent.h"

using namespace memecity::engine::ecs;

void DrawSystem::run(EntityManager& em) const
{
	float half_w = multimedia_manager.get_screen_width() / 2.0f;
	float half_h = multimedia_manager.get_screen_height() / 2.0f;

	auto& player = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_position_component = player.get<PositionComponent>();
	auto player_tex_position = player.get<DrawableComponent>()->get_texture().get_position();

	auto components = em.query<PositionComponent>()
		.where([&](PositionComponent& c) { 
		return c.x > player_position_component->x - half_w - 100 
			&& c.x < player_position_component->x + half_w + 100
			&& c.y > player_position_component->y - half_h - 100
			&& c.y < player_position_component->y + half_h + 100;
	}).to_vector();
	
	for (PositionComponent& entity_position_component : components)
	{	
		auto drawable_component = entity_position_component.entity().get<DrawableComponent>();

		auto& tex = drawable_component->get_texture();
		if (player_position_component->entity() != drawable_component->entity())
		{
			auto x = player_position_component->x - entity_position_component.x;
			auto y = player_position_component->y - entity_position_component.y;

			Vector2 tex_position{ player_tex_position.x - x, player_tex_position.y - y };
			tex.set_position(tex_position);
		}
		auto text_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&tex);
		text_texture ? multimedia_manager.render_texture(*text_texture) : multimedia_manager.render_texture(tex);
	}
}
