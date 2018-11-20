
#ifndef _ENTITY_H
#define  _ENTITY_H
#include <algorithm>
#include <vector>
#include "Type.h"
namespace memecity::engine::ecs {
	struct Component;
	struct Entity {
	protected:
		std::vector<std::reference_wrapper<Component>> _components;
	public:
		int id;
		Entity(int id) 
			: id(id) {}

		template<class T>
		bool add(T& component)
		{
			static_assert(std::is_convertible<T*, Component*>::value, "This function can only add concrete subclasses of Component");
			if (has<T>()) {
				return false;
			}
			_components.push_back(std::ref(component));
			return true;
		}

		template<class T>
		bool has() const
		{
			return std::any_of(_components.begin(), _components.end(), [](Component& c) { return token<T>() == typeid(c); });
		}

		template<class T>
		T* get() const
		{
			for (auto& component : _components) {
				if (token<T>() == typeid(component.get())) {
					return static_cast<T*>(&(component.get()));
				}
			}
			return nullptr;
		}

		bool operator==(const Entity& e) const { return id == e.id; }
		bool operator!=(const Entity& e) const { return id != e.id; }
	};
};
#endif
