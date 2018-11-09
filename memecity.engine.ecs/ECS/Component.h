#ifndef _COMPONENT_H
#define  _COMPONENT_H
#include "Entity.h"

namespace ecs {
	using component_typetoken = const char*;

	struct Component {
		Component() = default;
		const Entity& entity;
		Component(const Entity& e) : entity(e) {}
		Component(const Component &) = delete;
		Component(Component &&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;

		virtual component_typetoken get_type_token() const = 0;
		virtual ~Component() = default;
	};
};


#endif
