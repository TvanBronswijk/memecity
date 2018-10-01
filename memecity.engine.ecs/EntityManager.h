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
	void RegisterEntity(Entity &e);
	void RegisterComponent(Component &c);
	void RegisterSystem(System &s);
	void FireEvent(Event &e);
	void Update();
	~EntityManager();
};