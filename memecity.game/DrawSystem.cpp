#include "DrawSystem.h"
#include "DrawableComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
using namespace ecs;

void DrawSystem::run(EntityManager& em) const
{
	auto player_component = em.query<PlayerComponent>().first();
	auto player_position_component = em.get_component_of_entity<PositionComponent>(player_component->entity);
	auto drawable_components = em.get_components_of_type<DrawableComponent>();

	for (auto drawable_component : drawable_components)
	{
		if (drawable_component.get().entity != player_position_component->entity)
		{
			auto tex = drawable_component.get().texture;
			tex->translate({ (player_position_component->diffx*-1) , player_position_component->diffy });
		}
		drawable_component.get().texture->render();
	}
}



