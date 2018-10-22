#include <iostream> 
#include <map> 
#include <iterator> 
#ifndef _ENTITY_MANAGER_H
#define  _ENTITY_MANAGER_H
#include <vector>
#include "Entity.h"
#include "Component.h"
#include "System.h"
using namespace std;

class EntityManager {
private:
	int id = 0;
	vector<Entity*> entities;
	map<string, vector<Component*>> components;
	map<string, System*> systems;

public:
	EntityManager();
	~EntityManager();

	///<summary>Creates a new entity with an unused ID.</summary>
	Entity* create_entity();

	///<summary>Register a component to the EntityManager.</summary>
	void register_component(Component* c);

	///<summary>Register a system to the EntityManager.</summary>
	void register_system(System* s);

	///<summary>Get all entities</summary>
	vector<Entity*> get_entities();

	///<summary>Get all entities with a certain component.</summary>
	vector<Entity*> get_entities_with_component(string type);

	///<summary>Get components of a specific type.</summary>
	vector<Component*> get_components_of_type(string type);

	///<summary>Get specific component of entity</summary>
	Component* get_component_of_entity(int entity_id, string type);

	///<summary>Get components with a specific entity ID.</summary>
	vector<Component*> get_components_of_entity(int entity_id);

	///<summary>Checks if entity has component.</summary>
	bool has_component(Entity* e, string type);

	///<summary>Run all systems.</summary>
	void update();
};

#endif