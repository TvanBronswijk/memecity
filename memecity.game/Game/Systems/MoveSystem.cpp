#include "MoveSystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void MoveSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component<VelocityComponent>();

	for (auto& entity : entities)
	{
		auto current_position = entity.get().get<BaseComponent>();
		auto current_velocity_component = entity.get().get<VelocityComponent>();
		auto direction = AnimatedTexture::Direction::idle;

		if (current_velocity_component->x != 0)
		{
			direction = current_velocity_component->x > 0 ? AnimatedTexture::Direction::right : AnimatedTexture::Direction::left;

			current_position->location.x += current_velocity_component->x;
			current_velocity_component->x = 0;
		}

		if (current_velocity_component->y != 0)
		{
			direction = current_velocity_component->y > 0 ? AnimatedTexture::Direction::down : AnimatedTexture::Direction::up;

			current_position->location.y += current_velocity_component->y;
			current_velocity_component->y = 0;
		}

		move_event.fire(em, { entity, direction});
	}
}

void MoveSystem::on_collision(EntityManager& em, ColliderEventArgs ea)
{
	auto position_target = ea.target.get<BaseComponent>();
	auto position = ea.source.get<BaseComponent>();
	auto velocity = ea.source.get<VelocityComponent>();

	if (velocity != nullptr)
	{
		if (position_target->location.x > position->location.x)
		{
			velocity->x = -0.1f;
		}
		else if (position_target->location.x < position->location.x)
		{
			velocity->x = 0.1f;
		}
		if (position_target->location.y > position->location.y)
		{
			velocity->y = -0.1f;
		}
		else if (position_target->location.y < position->location.y)
		{
			velocity->y = 0.1f;
		}
	}
}
