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
	void register_entity(Entity &e);
	void register_component(Component &c);
	void register_system(System &s);
	void fire_event(Event &e);
	void Update();
	~EntityManager();
};