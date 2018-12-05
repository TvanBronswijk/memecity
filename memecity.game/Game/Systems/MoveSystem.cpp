#include "MoveSystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void MoveSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component<VelocityComponent>();
	for (const Entity& entity : entities)
	{
		auto base = entity.get<BaseComponent>();
		auto velocity = entity.get<VelocityComponent>();
		
		Vector2 diff{ velocity->x, velocity->y };
		base->location.x += diff.x;
		base->location.y += diff.y;
		velocity->x = 0;
		velocity->y = 0;
		
		auto animation_component = entity.get<AnimationComponent>();
		if (animation_component) {
			auto direction = AnimatedTexture::Direction::idle;
			if (diff.x != 0) direction = diff.x > 0 ? AnimatedTexture::Direction::right : AnimatedTexture::Direction::left;
			if (diff.y != 0) direction = diff.y > 0 ? AnimatedTexture::Direction::down : AnimatedTexture::Direction::up;
			animated_move_event.fire(em, { entity, direction });
		}
		
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
