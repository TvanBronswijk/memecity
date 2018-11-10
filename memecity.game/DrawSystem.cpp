#include "DrawSystem.h"
#include "DrawableComponent.h"
#include "PlayerComponent.h"
#include "PositionComponent.h"
using namespace ecs;

void DrawSystem::run(EntityManager& em) const
{
	auto player = em.get_entities_with_component<PlayerComponent>().front().get();
	auto entities = em.get_entities_with_component<DrawableComponent>();

	for (auto& entity : entities)
	{
		auto drawable = entity.get().get<DrawableComponent>();
		if (entity.get() != player)
		{
			auto player_position = player.get<PositionComponent>();
			drawable->texture->translate({ (player_position->diffx*-1) , player_position->diffy });
		}
		drawable->texture->render();
	}
}



