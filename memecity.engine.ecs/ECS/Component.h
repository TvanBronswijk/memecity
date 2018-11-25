#ifndef _COMPONENT_H
#define  _COMPONENT_H
#include "Entity.h"
namespace memecity::engine::ecs {
	struct Component {
	private:
		Entity* _entity;
	public:
		Component(Entity& e) : _entity(&e) {}
		Component(const Component &) = delete;
		Component(Component &&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(Component&&) = delete;
		const Entity& entity() const { return *_entity; }
		virtual ~Component() = default;
	};
};
#endif
