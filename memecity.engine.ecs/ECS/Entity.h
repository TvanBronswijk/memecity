#ifndef _ENTITY_H
#define  _ENTITY_H
#include <map>
#include "Type.h"
namespace memecity::engine::ecs {
	struct Component;
	struct Entity {
	protected:
		std::map<TypeToken, Component*> _components;
	public:
		int id;
		Entity(int id) 
			: id(id) {}

		template<class T>
		bool add(T& component)
		{
			static_assert(std::is_convertible<T*, Component*>::value, "This function can only add concrete subclasses of Component");
			if (!has<T>()) {
				_components[token<T>()] = &component;
				return true;
			}
			return false;
		}

		template<class T>
		bool has() const
		{
			return _components.find(token<T>()) != _components.end();
		}

		template<class T>
		T* get() const
		{
			if (has<T>()) {
				return static_cast<T*>(_components.at(token<T>()));
			}
			return nullptr;
		}

		bool operator==(const Entity& e) const { return id == e.id; }
		bool operator!=(const Entity& e) const { return id != e.id; }
	};
};
#endif
