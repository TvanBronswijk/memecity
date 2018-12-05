#ifndef _ENTITY_MANAGER_H
#define  _ENTITY_MANAGER_H
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <typeindex>
#include <vector>
#include "Component.h"
#include "Entity.h"
#include "Eventing/Event.h"
#include "System.h"
#include "Type.h"

namespace memecity::engine::ecs {
	class EntityManager {
	private:
		int back_id = 0;
		std::unordered_map<EntityType, std::vector<std::unique_ptr<Entity>>> entities;
		std::unordered_map<TypeToken, std::vector<std::unique_ptr<Component>>> components;
		std::unordered_map<System::Scope, std::unordered_map<TypeToken, std::unique_ptr<System>>> systems;

	public:
		EntityManager() = default;
		EntityManager(EntityManager&& em) = default;
		EntityManager& operator=(EntityManager&& em) = default;
		~EntityManager() = default;

		class EntityBuilder {
		private:
			EntityManager* em;
			Entity* entity;
		public:
			EntityBuilder(EntityManager& em, Entity& e) : em(&em), entity(&e) {};
			~EntityBuilder() = default;
			template<class T, class... Args>
			const EntityBuilder& with_component(Args&&... args) const
			{
				static_assert(std::is_convertible<T*, Component*>::value, "This function can only construct concrete subclasses of Component");
				static_assert(std::is_constructible<T, Entity&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
				em->create_component<T>(*entity, std::forward<Args>(args)...);
				return *this;
			}
			const Entity& get() const { return *entity; }
		};

		///<summary>Creates a new entity with an unused ID.</summary>
		EntityBuilder create_entity(EntityType type)
		{
			entities[type].push_back(std::make_unique<Entity>(back_id++, type));
			auto& new_entity = *entities[type].back();
			entity_created.fire(*this, new_entity);
			return EntityBuilder(*this, new_entity);
		}

		///<summary>Register a component to the EntityManager.</summary>
		template<class C, class... Args>
		C& create_component(Entity& e, Args&&... args)
		{
			static_assert(std::is_convertible<C*, Component*>::value, "This function can only construct concrete subclasses of Component");
			static_assert(std::is_constructible<C, Entity&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			components[token<C>()].push_back(std::make_unique<C>(e, std::forward<Args>(args)...));
			auto& new_component = *(static_cast<C*>(components[token<C>()].back().get()));
			e.add(new_component);
			component_created.fire(*this, new_component);
			return new_component;
		}

		///<summary>Register a system to the EntityManager.</summary>
		template<class S, class... Args>
		S& create_system(System::Scope scope = System::update, Args&&... args)
		{
			static_assert(std::is_convertible<S*, System*>::value, "This function can only construct concrete subclasses of System");
			static_assert(std::is_constructible<S, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			systems[scope][token<S>()] = std::make_unique<S>(std::forward<Args>(args)...);
			auto& new_system = *(static_cast<S*>(systems[scope][token<S>()].get()));
			system_created.fire(*this, new_system);
			return new_system;
		}

		///<summary>Get all entities</summary>
		std::vector<std::reference_wrapper<const Entity>> get_entities() const
		{
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
		std::vector<std::reference_wrapper<C>> get_components_of_type() {
			std::vector<std::reference_wrapper<C>> result;
			auto& components_of_type = components[token<C>()];
			std::transform(components_of_type.begin(), components_of_type.end(), std::back_inserter(result),
				[](auto& c) -> std::reference_wrapper<C> { return std::ref(*(static_cast<C*>(c.get()))); });
			return result;
		}

		template<class T>
		class ComponentQuery {
			static_assert(std::is_convertible<T*, Component*>::value, "This function can only construct concrete subclasses of Component");
			using Predicate = std::function<bool(T&)>;
		private:
			std::vector<std::reference_wrapper<T>> _collection;
		public:
			ComponentQuery(std::vector<std::reference_wrapper<T>> collection) : _collection(collection) {}
			~ComponentQuery() = default;
			ComponentQuery<T> where(Predicate predicate) const {
				std::vector<std::reference_wrapper<T>> result;
				std::copy_if(_collection.begin(), _collection.end(), std::back_inserter(result), predicate);
				return ComponentQuery<T>(result);
			}
			T* first(Predicate predicate) const {
				auto it = std::find_if(_collection.begin(), _collection.end(), predicate);
				if (it != _collection.end())
					return *it;
				return nullptr;
			}
			T* first() const {
				if (_collection.empty()) {
					return nullptr;
				}
				return &_collection.front().get();
			}
			std::vector<std::reference_wrapper<T>> to_vector() const { return _collection; }
		};

		///<summary>Get a query object.</summary>
		template<class C>
		ComponentQuery<C> query(){ return ComponentQuery<C>(get_components_of_type<C>()); }

		///<summary>Run all systems.</summary>
		void update(System::Scope scope = System::update)
		{
			for (auto& pair : systems[scope]) {
				pair.second->run(*this);
			}
		}

		eventing::Event<Entity&> entity_created;
		eventing::Event<Component&> component_created;
		eventing::Event<System&> system_created;
		
		eventing::Event<Entity&> entity_destroyed;
		eventing::Event<Component&> component_destroyed;
		eventing::Event<System&> system_destroyed;
	};
};
#endif
