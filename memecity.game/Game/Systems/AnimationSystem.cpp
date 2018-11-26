#include "AnimationSystem.h"
#include <Engine\Textures.h>

using namespace memecity::engine::texture;
using namespace memecity::engine::ecs;

void AnimationSystem::run(EntityManager& em) const
{
	auto animation_components = em.get_components_of_type<AnimationComponent>();
	for (AnimationComponent& animation_component : animation_components)
	{	
		const auto& current_position = animation_component.entity().get<PositionComponent>();
		auto& texture = animation_component.entity().get<DrawableComponent>()->get_texture();

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
