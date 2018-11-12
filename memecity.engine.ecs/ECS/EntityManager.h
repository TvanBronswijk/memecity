#ifndef _ENTITY_MANAGER_H
#define  _ENTITY_MANAGER_H
#include <typeindex>
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include "Type.h"
#include "Entity.h"
#include "Component.h"
#include "System.h"
#include "Query/Query.h"

namespace ecs {	
	using namespace query;
	class EntityManager {
	private:
		int last_id = 0;
		std::vector<Entity> entities;
		std::map<TypeToken, std::vector<std::unique_ptr<Component>>> components;
		std::map<System::Scope, std::map<TypeToken, std::unique_ptr<System>>> systems;

	public:
		///<summary>Creates a new entity with an unused ID.</summary>
		Entity& create_entity()
		{
			entities.emplace_back(++last_id);
			return entities.back();
		}

		///<summary>Register a component to the EntityManager.</summary>
		template<class C, class... Args>
		C& create_component(Args&&... args)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only construct concrete subclasses of Component");
			static_assert(std::is_constructible<C, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			components[token<C>()].emplace_back(std::make_unique<C>(std::forward<Args>(args)...));
			return *(static_cast<C*>(components[token<C>()].back().get()));
		}

		///<summary>Register a system to the EntityManager.</summary>
		template<class S, class... Args>
		S& create_system(System::Scope scope = System::update, Args&&... args)
		{
			static_assert(std::is_convertible<S*, System*>::value, "This function can only construct concrete subclasses of System");
			static_assert(std::is_constructible<S, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			systems[scope][token<S>()] = std::make_unique<S>(std::forward<Args>(args)...);
			return *(static_cast<S*>(systems[scope][token<S>()].get()));
		}

		///<summary>Get all entities</summary>
		std::vector<std::reference_wrapper<const Entity>> get_entities() const
		{
			return std::vector<std::reference_wrapper<const Entity>>(entities.begin(), entities.end());
		}

		///<summary>Get all entities with a certain component.</summary>
		template<class C>
		std::vector<std::reference_wrapper<const Entity>> get_entities_with_component() const
		{
			std::vector<std::reference_wrapper<const Entity>> result;
			for (auto& e : entities)
				if (e.has<C>())
					result.push_back(std::ref(e));
			return result;
		}

		///<summary>Get components of a specific type.</summary>
		template<class C>
		std::vector<std::reference_wrapper<C>> get_components_of_type()
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only retrieve concrete subclasses of Component");
			return ComponentQuery<C>(components[token<C>()])
				.to_vector();
		}

		///<summary>Get a query object.</summary>
		template<class C>
		ComponentQuery<C> query() 
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only retrieve concrete subclasses of Component");
			return ComponentQuery<C>(components[token<C>()]);
		}

		///<summary>Run all systems.</summary>
		void update(System::Scope scope = System::update)
		{
			for (auto& pair : systems[scope])
				pair.second->run(*this);
		}

		~EntityManager()
		{
			entities.clear();
			for (auto& pair : components)
				pair.second.clear();
			components.clear();
			for (auto& pair : systems)
				pair.second.clear();
			systems.clear();
		}
	};
};
#endif
