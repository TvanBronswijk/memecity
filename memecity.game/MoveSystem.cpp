#include "MoveSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
using namespace ecs;

void MoveSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component<VelocityComponent>();

	for (auto entity : entities)
	{
		auto current_position = entity.get().get<PositionComponent>();
		auto current_velocity_component = entity.get().get<VelocityComponent>();

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
	auto position_target = em.get_component_of_entity<PositionComponent>(ea.target, PositionComponent::COMPONENT_TYPE);
	auto position = em.get_component_of_entity<PositionComponent>(ea.source, PositionComponent::COMPONENT_TYPE);
	auto velocity = em.get_component_of_entity<VelocityComponent>(ea.source, VelocityComponent::COMPONENT_TYPE);

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
