#include "AnimationSystem.h"
#include <Engine\Textures.h>
#include "../Event/MoveEventArgs.h"
using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void AnimationSystem::run(EntityManager& em) const
{
}

void AnimationSystem::on_move(memecity::engine::ecs::EntityManager& em, MoveEventArgs ea)
{
	auto animation_component = ea.source.get<AnimationComponent>();
	const auto& current_velocity = ea.source.get<VelocityComponent>();
	auto& texture = ea.source.get<DrawableComponent>()->get_texture();

	// Cast from base class (Texture) to derived class (AnimatedTexture)
	auto animated_texture = dynamic_cast<AnimatedTexture*>(&texture);

	if (animated_texture != nullptr && current_velocity != nullptr)
	{
		animated_texture->update(_context->get_timer().get_delta_time());
		animated_texture->set_direction(AnimatedTexture::Direction::idle);

		if (animation_component->current_state == AnimationComponent::AnimationState::fighting)
		{
			animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::horizontal);
			animation_component->current_state = AnimationComponent::AnimationState::idle;
		}
		else
		{
			animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::vertical);
			animated_texture->set_direction(ea.direction);
		}
	}
}

