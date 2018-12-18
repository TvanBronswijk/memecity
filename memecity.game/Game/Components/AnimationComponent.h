#ifndef _ANIMATION_COMPONENT_H
#define _ANIMATION_COMPONENT_H

#include <ECS.h>

struct AnimationComponent : memecity::engine::ecs::Component
{
	enum class AnimationState { idle, fighting, dying };
	
	float animation_timer = 0.0f;
	AnimationState current_state;
	memecity::engine::texture::AnimatedTexture::AnimationState old_state;

	AnimationComponent(memecity::engine::ecs::Entity& entity) : Component(entity), current_state(AnimationState::idle),
	                                                            old_state(memecity::engine::texture::AnimatedTexture::AnimationState::idle)
	{
	}

	bool is_finished() const;
};

inline bool AnimationComponent::is_finished() const
{
	return animation_timer >= 2.0f;
}

#endif
