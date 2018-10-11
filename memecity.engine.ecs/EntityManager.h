#include <iostream> 
#include <map> 
#include <iterator> 
#include <vector>
#include "Entity.h"
#include "Component.h"
#include "System.h"
#include "Event.h"
using namespace std;

#ifndef _ENTITY_MANAGER_H
#define  _ENTITY_MANAGER_H

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

	///<summary>Get components of a specific type.</summary>
	vector<Component*> get_components_of_type(string type);

	///<summary>Get specific component of entity</summary>
	Component* get_component_of_entity(Entity* e, string type);

	///<summary>Get components with a specific entity ID.</summary>
	vector<Component*> get_components_of_entity(Entity* e);

	///<summary>Run all systems that are subscribed to the event.</summary>
	void fire_event(Event* e);

	///<summary>Run all systems.</summary>
	void update();
};

#endif