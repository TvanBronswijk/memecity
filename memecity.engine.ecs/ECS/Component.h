#ifndef _COMPONENT_H
#define  _COMPONENT_H
#include "Entity.h"
namespace ecs {
	struct Component {
		const Entity& entity;
		Component() = default;
		Component(const Entity& e) : entity(e) {}
		Component(const Component &) = delete;
		Component(Component &&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;
		virtual ~Component() = default;
	};
};
#endif
