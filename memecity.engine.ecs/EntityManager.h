#ifndef _ENTITY_MANAGER_H
#define  _ENTITY_MANAGER_H
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include "Entity.h"
#include "Component.h"
#include "System.h"

namespace ecs {
	class EntityManager {
	private:
		int last_id = -1;
		std::vector<Entity> entities;
		std::map<component_typetoken, std::vector<std::unique_ptr<Component>>> components;
		std::map<system_typetoken, std::unique_ptr<System>> systems;

	public:
		EntityManager() {}

		///<summary>Creates a new entity with an unused ID.</summary>
		Entity& create_entity()
		{
			entities.push_back(Entity(++last_id));
			return entities[last_id];
		}

		///<summary>Register a component to the EntityManager.</summary>
		template<class C, class... Args>
		C& create_component(Args&&... args)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only construct concrete subclasses of Component");
			static_assert(std::is_constructible<C, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			std::unique_ptr<C> component = std::make_unique<C>(std::forward<Args>(args)...);
			component_typetoken token = component->get_type_token();
			components[token].push_back(std::move(component));
			return *(dynamic_cast<C*>(components[token].back().get()));
		}

		///<summary>Register a system to the EntityManager.</summary>
		template<class S, class... Args>
		S& create_system(Args&&... args)
		{
			static_assert(std::is_convertible<S*, System*>::value, "This function can only construct concrete subclasses of System");
			static_assert(std::is_constructible<S, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			std::unique_ptr<S> system = std::make_unique<S>(std::forward<Args>(args)...);
			system_typetoken token = system->get_type_token();
			systems[token] = std::move(system);
			return *(dynamic_cast<S*>(systems[token].get()));
		}

		///<summary>Get all entities</summary>
		std::vector<std::reference_wrapper<Entity>> get_entities()
		{
			return std::vector<std::reference_wrapper<Entity>>(entities.begin(), entities.end());
		}

		///<summary>Get all entities with a certain component.</summary>
		std::vector<std::reference_wrapper<Entity>> get_entities_with_component(component_typetoken token)
		{
			std::vector<std::reference_wrapper<Entity>> result;
			for (auto& e : entities)
				if (this->has_component(e, token))
					result.push_back(std::ref(e));
			return result;
		}

		///<summary>Get components of a specific type.</summary>
		template<class C>
		std::vector<std::reference_wrapper<C>> get_components_of_type(component_typetoken token)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only retrieve concrete subclasses of Component");

			std::vector<std::reference_wrapper<C>> result;
			for (auto& c : components[token])
				result.push_back(std::ref(*(dynamic_cast<C*>(c.get()))));
			return result;
		}

		///<summary>Get specific component of entity</summary>
		template<class C>
		C* get_component_of_entity(Entity& entity, component_typetoken token)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only retrieve concrete subclasses of Component");
			for (auto& pairs : components)
				for (auto& c : pairs.second)
					if (c->entity == entity && c->get_type_token() == token)
						return dynamic_cast<C*>(c.get());
			return nullptr;
		}

		///<summary>Get components with a specific entity ID.</summary>
		template<class C>
		std::vector<std::reference_wrapper<C>> get_components_of_entity(Entity& entity)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only retrieve concrete subclasses of Component");
			std::vector<std::reference_wrapper<C>> result;
			for (auto& pairs : components)
				for (auto& c : pairs.second)
					if (c->entity == entity)
						result.push_back(std::ref(*(dynamic_cast<C*>(c.get()))));
			return result;
		}

		///<summary>Checks if entity has component.</summary>
		bool has_component(Entity& entity, component_typetoken token)
		{
			for (auto& c : components[token])
				if (c->entity == entity)
					return true;
			return false;
		}

		///<summary>Run all systems.</summary>
		void update()
		{
			for (auto& pair : systems)
				pair.second->run(*this);
		}

		~EntityManager()
		{
			entities.clear();
			for (auto& pair : components)
			{
				pair.second.clear();
			}
			components.clear();
			systems.clear();
		}
	};
};



#endif