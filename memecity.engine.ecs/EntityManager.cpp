#include "EntityManager.h"

EntityManager::EntityManager()
{

}

void EntityManager::RegisterEntity(Entity &e)
{
	entities.push_back(e);
}

void EntityManager::RegisterComponent(Component &c)
{
	components[c.getType()].push_back(c);
}

void EntityManager::RegisterSystem(System &s)
{
	
	systems[s.getType()] = s;
}

void EntityManager::FireEvent(Event &e)
{
	for (auto pair : systems)
		if(pair.second.isOnEvent(e))
			pair.second.Run(*this, e);
}

void EntityManager::Update() 
{
	for (auto pair : systems)
		pair.second.Run(*this);
}

EntityManager::~EntityManager()
{

}
