#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H
#include <unordered_map>
#include "Type.h"
#include "Component.h"

namespace memecity::engine::ecs {
	struct Entity {
	private:
		friend class EntityManager;
		std::unordered_map<TypeToken, Component*> _components;
	public:
		int id;
		EntityType type;
		Entity(int id, EntityType type) : id(id), type(type) {}
		template<class T>
		bool has() const { return _components.find(token<T>()) != _components.end(); }
		template<class T>
		T* get() const { return has<T>() ? static_cast<T*>(_components.at(token<T>())) : nullptr; }
		bool operator==(const Entity& e) const { return id == e.id; }
		bool operator!=(const Entity& e) const { return id != e.id; }
	};
}

#endif
