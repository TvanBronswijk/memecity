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
		auto direction = AnimatedTexture::Direction::idle;

		if (current_velocity_component->x != 0)
		{
			direction = current_velocity_component->x > 0 ? AnimatedTexture::Direction::right : AnimatedTexture::Direction::left;

			current_position->x += current_velocity_component->x;
			current_velocity_component->x = 0;
		}

		if (current_velocity_component->y != 0)
		{
			direction = current_velocity_component->y > 0 ? AnimatedTexture::Direction::down : AnimatedTexture::Direction::up;

			current_position->y += current_velocity_component->y;
			current_velocity_component->y = 0;
		}

		move_event.fire(em, { entity, direction});
	}
}

void MoveSystem::on_collision(EntityManager& em, ColliderEventArgs args)
{
	auto position = args.source.get<PositionComponent>();
	auto velocity = args.source.get<VelocityComponent>();

	if (velocity != nullptr)
	{
		position->x += args.source_rectangle.x < args.target_rectangle.x ? -(velocity->x) - 1.0f : (velocity->x) + 1.0f;
		position->y += args.source_rectangle.y < args.target_rectangle.y ? -(velocity->y) - 1.0f : (velocity->y) + 1.0f;
		velocity->x = 0;
		velocity->y = 0;
	}
}
