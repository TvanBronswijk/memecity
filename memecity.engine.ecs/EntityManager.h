#include <iostream> 
#include <map> 
#include <iterator> 
#include <list>
#include "Entity.h"
#include "Component.h"
#include "System.h"
#include "Event.h"

class EntityManager {
private:
	std::list<Entity> entities;
	std::map<std::string, std::list<Component>> components;
	std::map<std::string, System> systems;

public:
	EntityManager();
	~EntityManager();

	///<summary>Register an entity to the EntityManager.</summary>
	void register_entity(Entity &e);

	///<summary>Register a component to the EntityManager.</summary>
	void register_component(Component &c);

	///<summary>Register a system to the EntityManager.</summary>
	void register_system(System &s);

	///<summary>Run all systems that are subscribed to the event.</summary>
	void fire_event(Event &e);

	///<summary>Run all systems.</summary>
	void Update();
};