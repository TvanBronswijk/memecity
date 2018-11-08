#ifndef _COMPONENT_H
#define  _COMPONENT_H
#include "Entity.h"

namespace ecs {
	using component_typetoken = const char*;

	struct Component {
		const Entity& entity;
		Component(const Entity& e) : entity(e)
		{	
		}
		Component(const Component &) = delete;
		Component(Component &&) = delete;
		virtual component_typetoken get_type_token() const = 0;
		virtual ~Component() {}
	};
};


#endif