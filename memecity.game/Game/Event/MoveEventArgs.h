#ifndef _MOVE_EVENT_ARGS_H
#define _MOVE_EVENT_ARGS_H
#include <ECS.h>

struct MoveEventArgs : public memecity::engine::ecs::eventing::EventArgs
{
	const memecity::engine::ecs::Entity &source;
	memecity::engine::texture::AnimatedTexture::Direction direction;

	MoveEventArgs(const memecity::engine::ecs::Entity& source, memecity::engine::texture::AnimatedTexture::Direction direction)
		: source(source), direction(direction) {}
};

#endif
