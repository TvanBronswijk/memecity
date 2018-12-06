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
		auto direction = AnimatedTexture::AnimationState::idle;

		const auto current_velocity_component = entity.get().get<VelocityComponent>();
		
		if (current_velocity_component->x != 0)
		{
			direction = current_velocity_component->x > 0 ? AnimatedTexture::AnimationState::walk_right : AnimatedTexture::AnimationState::walk_left;

			current_position->x += current_velocity_component->x;
			current_velocity_component->x = 0;
		}

		if (current_velocity_component->y != 0)
		{
			direction = current_velocity_component->y > 0 ? AnimatedTexture::AnimationState::walk_down : AnimatedTexture::AnimationState::walk_up;

			current_position->y += current_velocity_component->y;
			current_velocity_component->y = 0;
		}

		move_event.fire(em, { entity, direction});
	}
}

void MoveSystem::on_collision(EntityManager& em, ColliderEventArgs ea) const
{
	const auto position_target = ea.target.get<PositionComponent>();
	const auto position = ea.source.get<PositionComponent>();
	const auto velocity = ea.source.get<VelocityComponent>();

	if (velocity != nullptr)
	{
		if (position_target->x > position->x)
		{
			velocity->x = -1.0f;
		}
		else if (position_target->x < position->x)
		{
			velocity->x = 1.0f;
		}
		if (position_target->y > position->y)
		{
			velocity->y = -1.0f;
		}
		else if (position_target->y < position->y)
		{
			velocity->y = 1.0f;
		}
	}
}
