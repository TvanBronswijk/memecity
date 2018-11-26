#include "MoveSystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void MoveSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component<VelocityComponent>();

	for (auto& entity : entities)
	{
		auto current_position = entity.get().get<PositionComponent>();
		auto current_velocity_component = entity.get().get<VelocityComponent>();
		auto& player_component = em.get_components_of_type<PlayerComponent>()[0].get();

		if (entity.get().id == player_component.entity().id) {
#ifdef DEBUG
			std::cout << "x: " <<current_position->x << " y: " << current_position->y << "\n";
			std::cout << "diffx: " << current_position->diffx << " diffy: " << current_position->diffy << "\n";
#endif
		}

		if (current_velocity_component->x != 0)
		{
			current_position->x += current_velocity_component->x;
			current_position->diffx = current_velocity_component->x;
			current_velocity_component->x = 0;
		}
		else
		{
			current_position->diffx = 0;
		}

		if (current_velocity_component->y != 0)
		{
			current_position->y += current_velocity_component->y;
			current_position->diffy = current_velocity_component->y;
			current_velocity_component->y = 0;
		}
		else
		{
			current_position->diffy = 0;
		}
	}
}

void MoveSystem::on_collision(EntityManager& em, ColliderEventArgs ea)
{
	auto position_target = ea.target.get<PositionComponent>();
	auto position = ea.source.get<PositionComponent>();
	auto velocity = ea.source.get<VelocityComponent>();

	if (velocity != nullptr)
	{
		if (position_target->x > position->x)
		{
			position->x -= 5;
			position->diffx = -5;
		}
		else if (position_target->x < position->x)
		{
			position->x += 5;
			position->diffx = 5;
		}
		if (position_target->y > position->y)
		{
			position->y -= 5;
			position->diffy = -5;
		}
		else if (position_target->y < position->y)
		{
			position->y += 5;
			position->diffy = 5;
		}
	}
}
