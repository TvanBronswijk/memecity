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
	auto animation_component = args.source.get<AnimationComponent>();
	const auto& current_velocity = args.source.get<VelocityComponent>();
	auto& texture = args.source.get<BaseComponent>()->get_texture();

	// Cast from base class (Texture) to derived class (AnimatedTexture)
	auto animated_texture = dynamic_cast<AnimatedTexture*>(&texture);

	if (animated_texture != nullptr && current_velocity != nullptr)
	{
		animated_texture->update(_context->get_timer().get_delta_time());
		animated_texture->set_state(AnimatedTexture::AnimationState::idle);

		// TEST FOR DYING
		if (animation_component->current_state == AnimationComponent::AnimationState::dying)
		{
			animated_texture->set_state(AnimatedTexture::AnimationState::dying);
		}
		else if (animation_component->current_state == AnimationComponent::AnimationState::fighting)
		{
			animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::horizontal);
			animation_component->current_state = AnimationComponent::AnimationState::idle;
		}
		else
		{
			animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::vertical);
			animated_texture->set_state(args.state);
		}
	}
}
