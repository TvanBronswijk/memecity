#include "DrawSystem.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"
#include "TextTexture.h"

using namespace ecs;

system_typetoken DrawSystem::SYSTEM_TYPE = "DrawSystem";

DrawSystem::DrawSystem(MultimediaManager &multimedia_manager) : multimedia_manager(multimedia_manager)
{
}

void DrawSystem::run(EntityManager& em) const
{
	auto player_components = em.get_components_of_type<PlayerComponent>(PlayerComponent::COMPONENT_TYPE);
	auto player_position_component = em.get_component_of_entity<PositionComponent>(player_components[0].get().entity, PositionComponent::COMPONENT_TYPE);

	auto drawable_components = em.get_components_of_type<DrawableComponent>(DrawableComponent::COMPONENT_TYPE);

	multimedia_manager.clear_graphics();

	for (auto& drawable_component : drawable_components)
	{
		auto tex = drawable_component.get().texture.get();
		if (drawable_component.get().entity != player_position_component->entity)
		{
			tex->translate({ (player_position_component->diffx*-1) , player_position_component->diffy });
		}

		auto text_texture = dynamic_cast<TextTexture*>(&*tex);
		if (text_texture == nullptr)
		{
			multimedia_manager.render_texture(*tex);
		}
		else
		{
			multimedia_manager.render_text_texture(*text_texture);
		}
	}

	multimedia_manager.render_graphics();
}



