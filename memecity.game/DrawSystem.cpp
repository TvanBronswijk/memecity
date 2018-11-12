#include "DrawSystem.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"
#include "TextTexture.h"

using namespace ecs;

void DrawSystem::run(EntityManager& em) const
{
	auto& player_component = em.get_entities_with_component<PlayerComponent>().front().get();
	auto player_position_component = player_component.get<PositionComponent>();

	auto drawable_components = em.get_components_of_type<DrawableComponent>();

	for (auto& drawable_component : drawable_components)
	{
		auto& tex = drawable_component.get().get_texture();
		if (drawable_component.get().entity != player_position_component->entity)
		{
			tex.translate({ (player_position_component->diffx*-1) , player_position_component->diffy });
		}

		auto text_texture = dynamic_cast<TextTexture*>(&tex);
		if (text_texture)
		{
			multimedia_manager.render_text_texture(*text_texture);
		}
		else
		{
			multimedia_manager.render_texture(tex);
		}
	}
}



