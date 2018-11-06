#ifndef _ENTITY_MANAGER_H
#define  _ENTITY_MANAGER_H
#include <iostream> 
#include <map> 
#include <iterator> 
#include <vector>
#include "Entity.h"
#include "Component.h"
#include "System.h"

namespace ecs {
	class EntityManager {
	private:
		int id = 0;
		std::vector<Entity*> entities;
		std::map<std::string, std::vector<Component*>> components;
		std::map<std::string, System*> systems;

	public:
		EntityManager();

		///<summary>Creates a new entity with an unused ID.</summary>
		Entity* create_entity();

		///<summary>Register a component to the EntityManager.</summary>
		void register_component(Component* c);

		///<summary>Register a system to the EntityManager.</summary>
		void register_system(System* s);

		///<summary>Get all entities</summary>
		std::vector<Entity*> get_entities();

		///<summary>Get all entities with a certain component.</summary>
		std::vector<Entity*> get_entities_with_component(std::string type);

		///<summary>Get components of a specific type.</summary>
		std::vector<Component*> get_components_of_type(std::string type);

		///<summary>Get specific component of entity</summary>
		Component* get_component_of_entity(int entity_id, std::string type);

		///<summary>Get components with a specific entity ID.</summary>
		std::vector<Component*> get_components_of_entity(int entity_id);

		///<summary>Checks if entity has component.</summary>
		bool has_component(Entity* e, std::string type);

		///<summary>Run all systems.</summary>
		void update();

		~EntityManager();
	};
};



#endif