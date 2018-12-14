#ifndef _ANIMATION_COMPONENT_H
#define _ANIMATION_COMPONENT_H

#include <ECS.h>

struct AnimationComponent : memecity::engine::ecs::Component
{
	enum class AnimationState { idle, fighting, dying };

	int dead_counter = 0;

	AnimationState current_state;
	//memecity::engine::texture::AnimatedTexture::AnimationState direction;
	AnimationComponent(memecity::engine::ecs::Entity& entity) : Component(entity), current_state(AnimationState::idle) {}
};

#endif
