#include "DrawSystem.h"

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

	for (auto drawable_component : drawable_components)
	{
		if (drawable_component.get().entity != player_position_component->entity)
		{
			auto tex = drawable_component.get().texture;
			tex->translate({ (player_position_component->diffx*-1) , player_position_component->diffy });
		}
	}

	multimedia_manager.clear_graphics();
	for (auto component : drawable_components)
	{
		component.get().texture->render();
	}
	multimedia_manager.render_graphics();
}



