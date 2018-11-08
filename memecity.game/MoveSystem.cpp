#include "MoveSystem.h"

using namespace ecs;

system_typetoken MoveSystem::SYSTEM_TYPE = "MoveSystem";

MoveSystem::MoveSystem() : System()
{

}

void MoveSystem::run(EntityManager& em) const
{
	auto components = em.get_components_of_type<VelocityComponent>(VelocityComponent::COMPONENT_TYPE);

	for (auto velocity_component : components)
	{
		auto current_position = em.get_component_of_entity<PositionComponent>(velocity_component.get().entity, PositionComponent::COMPONENT_TYPE);
		const auto current_velocity_component = velocity_component;

		if (current_velocity_component.get().x != 0)
		{
			current_position->x += current_velocity_component.get().x;
			current_position->diffx = current_velocity_component.get().x;
			current_velocity_component.get().x = 0;
		}
		else
		{
			current_position->diffx = 0;
		}

		if (current_velocity_component.get().y != 0)
		{
			current_position->y += current_velocity_component.get().y;
			current_position->diffy = current_velocity_component.get().y;
			current_velocity_component.get().y = 0;
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
