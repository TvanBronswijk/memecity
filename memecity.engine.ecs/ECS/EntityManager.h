#ifndef _ENTITY_MANAGER_H
#define  _ENTITY_MANAGER_H
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <iterator>
#include <map>
#include <typeindex>
#include <vector>
#include "Query/Query.h"
#include "Entity.h"
#include "Component.h"
#include "Eventing/Event.h"
#include "System.h"
#include "Type.h"

namespace memecity::engine::ecs {
	class EntityManager {
	private:
		int back_id = 0;
		mutable std::mutex entity_mutex;
		mutable std::mutex component_mutex;
		std::unordered_map<EntityType, std::vector<std::unique_ptr<Entity>>> entities;
		std::unordered_map<TypeToken, std::vector<std::unique_ptr<Component>>> components;
		std::vector<std::unique_ptr<Entity>> deleted_entities;
		std::vector<std::unique_ptr<Component>> deleted_components;
	public:
		EntityManager() = default;
		EntityManager(EntityManager&& em) = default;
		EntityManager& operator=(EntityManager&& em) = default;
		~EntityManager() = default;

		class Builder {
		private:
			friend class EntityManager;
			EntityManager* em;
			Entity* entity;
			Builder(EntityManager& em, Entity& e) : em(&em), entity(&e) {};
		public:
			~Builder() = default;
			template<class T, class... Args>
			const Builder& with_component(Args&&... args) const
			{
				em->create_component<T>(*entity, std::forward<Args>(args)...);
				return *this;
			}
			const Entity& get() const { return *entity; }
		};

		///<summary>Creates a new entity with an unused ID.</summary>
		Builder create_entity(EntityType type)
		{
			entities[type].push_back(std::make_unique<Entity>(back_id++, type));
			auto& new_entity = *entities[type].back();
			entity_created.fire(*this, new_entity);
			return Builder(*this, new_entity);
		}

		///<summary>Get all entities</summary>
		std::vector<std::reference_wrapper<const Entity>> get_entities() const
		{
			std::lock_guard lock(entity_mutex);
			std::vector<std::reference_wrapper<const Entity>> result;
			std::for_each(entities.begin(), entities.end(),
				[&](auto& pair) {
				std::transform(pair.second.begin(), pair.second.end(), std::back_inserter(result),
					[&](auto& e)->std::reference_wrapper<const Entity> {
					return std::ref(*e);
				});
			});
			return result;
		}

		///<summary>Get entities by type</summary>
		std::vector<std::reference_wrapper<const Entity>> get_entities_by_type(EntityType type) const
		{
			std::lock_guard lock(entity_mutex);
			std::vector<std::reference_wrapper<const Entity>> result;
			auto& typed_entities = entities.at(type);
			std::transform(typed_entities.begin(), typed_entities.end(), std::back_inserter(result), [](auto& e)->std::reference_wrapper<const Entity> {
				return std::ref(*e.get());
			});
			return result;
		}

		///<summary>Get all entities with a certain component.</summary>
		template<class C>
		std::vector<std::reference_wrapper<const Entity>> get_entities_with_component() const
		{
			std::lock_guard lock(entity_mutex);
			std::lock_guard lock2(component_mutex);
			std::vector<std::reference_wrapper<const Entity>> result;
			auto& entity_components = (*components.find(token<C>())).second;
			std::transform(entity_components.begin(), entity_components.end(), 
				std::back_inserter(result), [](auto& c)->std::reference_wrapper<const Entity> {
				return std::ref(c->entity());
			});
			return result;
		}

		///<summary>Get a query object.</summary>
		Query<const Entity> query_all_entities() {
			return Query<const Entity>(get_entities());
		}

		///<summary>Get a query object.</summary>
		Query<const Entity> query_entities(EntityType type) {
			return Query<const Entity>(get_entities_by_type(type));
		}

		void remove_entity(const Entity& entity) {
			std::lock_guard lock(entity_mutex);
			entity_destroyed.fire(*this, entity);
			std::for_each(entity._components.begin(), entity._components.end(), [&](auto& pair) {
				remove_component(*pair.second);
			});

			std::for_each(entities.begin(), entities.end(), [&](auto& pair) {
				auto& entity_type = pair.second;
				std::copy_if(std::make_move_iterator(entity_type.begin()), std::make_move_iterator(entity_type.end()), 
					std::back_inserter(deleted_entities), [&](auto&& e) { return (*e) == entity; });
				entity_type.erase(std::remove_if(entity_type.begin(), entity_type.end(), [](auto& e) { return e ? false : true; }), entity_type.end());
			});
		}

		///<summary>Register a component to the EntityManager.</summary>
		template<class C, class... Args>
		C& create_component(Entity& e, Args&&... args)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only construct concrete subclasses of Component");
			static_assert(std::is_constructible<C, Entity&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			components[token<C>()].push_back(std::make_unique<C>(e, std::forward<Args>(args)...));
			auto& new_component = *(static_cast<C*>(components[token<C>()].back().get()));
			e._components[token<C>()] = &new_component;
			component_created.fire(*this, new_component);
			return new_component;
		}

		///<summary>Get components of a specific type.</summary>
		template<class C>
		std::vector<std::reference_wrapper<C>> get_components_of_type() {
			std::lock_guard lock(component_mutex);
			std::vector<std::reference_wrapper<C>> result;
			auto& components_of_type = components[token<C>()];
			std::transform(components_of_type.begin(), components_of_type.end(), std::back_inserter(result),
				[](auto& c) -> std::reference_wrapper<C> { return std::ref(*(static_cast<C*>(c.get()))); });
			return result;
		}

		///<summary>Get a query object.</summary>
		template<class C>
		Query<C> query_components() {
			return Query<C>(get_components_of_type<C>());
		}

		void remove_component(const Component& component) {
			std::lock_guard lock(component_mutex);
			component_destroyed.fire(*this, component);
			std::for_each(components.begin(), components.end(), [&](auto& pair) {
				auto& component_type = pair.second;
				std::copy_if(std::make_move_iterator(component_type.begin()), std::make_move_iterator(component_type.end()), 
					std::back_inserter(deleted_components), [&](auto&& c) { return (c.get()) == &component; });
				component_type.erase(std::remove_if(component_type.begin(), component_type.end(), [](auto& c) { return c ? false : true; }), component_type.end());
			});
		}

		void cleanup() {
			deleted_entities.clear();
			deleted_components.clear();
		}

		eventing::Event<const Entity&> entity_created;
		eventing::Event<const Entity&> entity_destroyed;
		eventing::Event<const Component&> component_created;
		eventing::Event<const Component&> component_destroyed;
	};
};
#endif
