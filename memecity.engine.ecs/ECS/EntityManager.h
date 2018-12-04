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

namespace memecity::engine::ecs {
	using namespace query;
	class EntityManager {
	private:
		int back_id = 0;
		std::vector<std::unique_ptr<Entity>> entities;
		std::unordered_map<EntityType, std::vector<Entity*>> entities_by_type;
		std::unordered_map<TypeToken, std::vector<std::unique_ptr<Component>>> components;
		std::unordered_map<System::Scope, std::unordered_map<TypeToken, std::unique_ptr<System>>> systems;

		template<class C>
		std::vector<std::reference_wrapper<C>> get_components() {
			std::vector<std::reference_wrapper<C>> result;
			auto& components_of_type = components[token<C>()];
			std::transform(components_of_type.begin(), components_of_type.end(), std::back_inserter(result),
				[](auto& c) -> std::reference_wrapper<C> { return std::ref(*(static_cast<C*>(c.get()))); });
			return result;
		}

	public:
		EntityManager() = default;
		EntityManager(EntityManager&& em) = default;
		EntityManager& operator=(EntityManager&& em) = default;

		///<summary>Creates a new entity with an unused ID.</summary>
		Entity& create_entity(EntityType type)
		{
			entities.push_back(std::make_unique<Entity>(back_id++, type));
			entities_by_type[type].push_back(entities.back().get());
			return *entities.back();
		}

		///<summary>Register a component to the EntityManager.</summary>
		template<class C, class... Args>
		C& create_component(Entity& e, Args&&... args)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only construct concrete subclasses of Component");
			static_assert(std::is_constructible<C, Entity&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			components[token<C>()].push_back(std::make_unique<C>(e, std::forward<Args>(args)...));
			C& result = *(static_cast<C*>(components[token<C>()].back().get()));
			e.add(result);
			return result;
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
			std::vector<std::reference_wrapper<const Entity>> result;
			std::transform(entities.begin(), entities.end(), std::back_inserter(result), [](auto& e)->std::reference_wrapper<const Entity> {
				return std::ref(*e);
			});
			return result;
		}

		///<summary>Get entities by type</summary>
		std::vector<std::reference_wrapper<const Entity>> get_entities_by_type(EntityType type) const
		{
			std::vector<std::reference_wrapper<const Entity>> result;
			auto& typed_entities = entities_by_type.at(type);
			std::transform(typed_entities.begin(), typed_entities.end(), std::back_inserter(result), [](auto& e)->std::reference_wrapper<const Entity> {
				return std::ref(*e);
			});
			return result;
		}

		///<summary>Get all entities with a certain component.</summary>
		template<class C>
		std::vector<std::reference_wrapper<const Entity>> get_entities_with_component() const
		{
			std::vector<std::reference_wrapper<const Entity>> result;
			auto& entity_components = (*components.find(token<C>())).second;
			std::transform(entity_components.begin(), entity_components.end(), std::back_inserter(result), 
				[](auto& c)->std::reference_wrapper<const Entity> {
				return std::ref(c->entity());
			});
			return result;
		}

		///<summary>Get components of a specific type.</summary>
		template<class C>
		std::vector<std::reference_wrapper<C>> get_components_of_type()
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only retrieve concrete subclasses of Component");
			return ComponentQuery<C>(get_components<C>())
				.to_vector();
		}

		///<summary>Get a query object.</summary>
		template<class C>
		ComponentQuery<C> query()
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only retrieve concrete subclasses of Component");
			return ComponentQuery<C>(get_components<C>());
		}

		///<summary>Run all systems.</summary>
		void update(System::Scope scope = System::update)
		{
			for (auto& pair : systems[scope]) {
				pair.second->run(*this);
			}
		}

		~EntityManager()
		{
			entities.clear();
			for (auto& pair : components) {
				pair.second.clear();
			}
			components.clear();
			for (auto& pair : systems) {
				pair.second.clear();
			}
			systems.clear();
		}
	};
};
#endif
