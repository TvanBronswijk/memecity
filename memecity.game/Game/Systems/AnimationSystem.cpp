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

		if (animated_texture != nullptr && current_position != nullptr)
		{
			animated_texture->update();
			animated_texture->set_state(AnimatedTexture::AnimationState::idle);

			// TEST FOR DYING
			if (animation_component.current_state == AnimationComponent::AnimationState::dying)
			{
				animated_texture->set_state(AnimatedTexture::AnimationState::dying);
			}  
			else if (animation_component.current_state == AnimationComponent::AnimationState::fighting)
			{
				animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::horizontal);
				animation_component.current_state = AnimationComponent::AnimationState::idle;
			}
			else
			{
				animated_texture->set_animation_direction(AnimatedTexture::AnimationDirection::vertical);

				if (current_position->diffx > 0)
				{
					animated_texture->set_state(AnimatedTexture::AnimationState::walk_right);
				}
				else if (current_position->diffx < 0)
				{
					animated_texture->set_state(AnimatedTexture::AnimationState::walk_left);
				}
				else if (current_position->diffy > 0)
				{
					animated_texture->set_state(AnimatedTexture::AnimationState::walk_up);
				}
				else if (current_position->diffy < 0)
				{
					animated_texture->set_state(AnimatedTexture::AnimationState::walk_down);
				}
			}
		}
	}
}

