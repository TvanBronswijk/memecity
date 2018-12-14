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
			auto direction = AnimatedTexture::AnimationState::idle;
			if (diff.x != 0) direction = diff.x > 0 ? AnimatedTexture::AnimationState::right : AnimatedTexture::AnimationState::left;
			if (diff.y != 0) direction = diff.y > 0 ? AnimatedTexture::AnimationState::down : AnimatedTexture::AnimationState::up;
			//animation_component->direction = direction;
			//auto direction = AnimatedTexture::AnimationState::idle;
			//if (diff.x != 0) direction = diff.x > 0 ? AnimatedTexture::AnimationState::right : AnimatedTexture::AnimationState::left;
			//if (diff.y != 0) direction = diff.y > 0 ? AnimatedTexture::AnimationState::down : AnimatedTexture::AnimationState::up;
			animated_move_event.fire(em, { entity, direction });
		}
		
	}
}

void MoveSystem::on_collision(EntityManager& em, ColliderEventArgs args)
{
	auto base = args.source.get<BaseComponent>();
	auto velocity = args.source.get<VelocityComponent>();

	if (velocity != nullptr)
	{
		base->location.x += args.source_rectangle.x < args.target_rectangle.x ? -(velocity->x) - 5.0f : (velocity->x) + 5.0f;
		base->location.y += args.source_rectangle.y < args.target_rectangle.y ? -(velocity->y) - 5.0f : (velocity->y) + 5.0f;
		velocity->x = 0;
		velocity->y = 0;
	}
}
