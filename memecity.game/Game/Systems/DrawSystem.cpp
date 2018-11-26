#include "DrawSystem.h"
#include <Engine\Textures.h>
#include "../Components/VelocityComponent.h"

using namespace memecity::engine::ecs;

void DrawSystem::run(EntityManager& em) const
{
	auto& player = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_position_component = player.get<PositionComponent>();
	auto player_tex_position = player.get<DrawableComponent>()->get_texture().get_position();

	auto drawable_components = em.get_components_of_type<DrawableComponent>();
	
	for (DrawableComponent& drawable_component : drawable_components)
	{	
		auto& tex = drawable_component.get_texture();
		auto entity_position_component = drawable_component.entity().get<PositionComponent>();
		if (player_position_component->entity() != drawable_component.entity() && entity_position_component != nullptr)
		{
			auto x = player_position_component->x - entity_position_component->x;
			auto y = player_position_component->y - entity_position_component->y;

			Vector2 tex_position{ player_tex_position.x - x, player_tex_position.y - y };
			tex.set_position(tex_position);
		}
		auto text_texture = dynamic_cast<memecity::engine::texture::TextTexture*>(&tex);
		text_texture ? multimedia_manager.render_texture(*text_texture) : multimedia_manager.render_texture(tex);
	}
}
