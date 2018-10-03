#include "EntityManager.h"

EntityManager::EntityManager()
{

}

void EntityManager::register_entity(Entity &e)
{
	entities.push_back(e);
}

void EntityManager::register_component(Component &c)
{
	components[c.get_type()].push_back(c);
}

void EntityManager::register_system(System &s)
{
	
	systems[s.get_type()] = s;
}

void EntityManager::fire_event(Event &e)
{
	for (auto pair : systems)
		if(pair.second.is_on_event(e))
			pair.second.run(*this, e);
}

void EntityManager::Update() 
{
	for (auto pair : systems)
		pair.second.run(*this);
}

EntityManager::~EntityManager()
{

}
