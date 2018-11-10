#include "DrawSystem.h"
#include "DrawableComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
using namespace ecs;

void DrawSystem::run(EntityManager& em) const
{
	auto player = em.get_entities_with_component<PlayerComponent>().front().get();
	
	auto components = em.get_components_of_type<DrawableComponent>();
	for (auto& drawable : components)
	{
		if (drawable.get().entity != player)
		{
			auto player_position = player.get<PositionComponent>();
			drawable.get().texture->translate({ (player_position->diffx*-1) , player_position->diffy });
		}
		drawable.get().texture->render();
	}
}



