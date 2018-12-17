#ifndef _TILE_COMPONENT
#define _TILE_COMPONENT
#include "ECS/Component.h"

struct TileComponent : public memecity::engine::ecs::Component
{
protected:
	char _character;

public:
	TileComponent(memecity::engine::ecs::Entity& entity, char character)
		: Component(entity), _character(character) {}
	char get_character() const { return _character; }
};

#endif

