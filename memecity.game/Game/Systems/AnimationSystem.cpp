#include "AnimationSystem.h"
#include <Engine\Textures.h>
#include "../Event/MoveEventArgs.h"
using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void AnimationSystem::run(EntityManager& em) const
{
}

void AnimationSystem::on_move(memecity::engine::ecs::EntityManager& em, MoveEventArgs args)
{
	auto animation = args.source.get<AnimationComponent>();
	auto base = args.source.get<BaseComponent>();
	auto animated_texture = static_cast<AnimatedTexture*>(&base->get_texture());
	
	animated_texture->update(_context->get_timer().get_delta_time());
	animated_texture->set_direction(AnimatedTexture::Direction::idle);
	switch (animation->current_state) {
	case AnimationComponent::AnimationState::fighting:
		animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::horizontal);
		animation->current_state = AnimationComponent::AnimationState::idle;
		break;
	case AnimationComponent::AnimationState::idle:
		animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::vertical);
		animated_texture->set_direction(args.direction);
		break;
	}
}

