#include "EntityManager.h"

EntityManager::EntityManager()
{

}

Entity* EntityManager::create_entity()
{
	auto e = new Entity(id++);
	entities.push_back(e);
	return e;
}

void EntityManager::register_component(Component* c)
{
	components[c->get_type()].push_back(c);
}

void EntityManager::register_system(System* s)
{
	systems[s->get_type()] = s;
}

vector<Component*> EntityManager::get_components_of_type(string type)
{
	return components[type];
}

Component* EntityManager::get_component_of_entity(Entity* e, string type)
{
	for (auto pairs : components)
		for (auto c : pairs.second)
			if (c->entity_id == e->id && c->get_type() == type)
				return c;
	return nullptr;
}

vector<Component*> EntityManager::get_components_of_entity(Entity* e)
{
	vector<Component*> result;
	for (auto pairs : components)
		for (auto c : pairs.second)
			if (c->entity_id == e->id)
				result.push_back(c);
	return result;
}

void EntityManager::fire_event(Event* e)
{
	for (auto pair : systems)
		if(pair.second->is_on_event(e))
			pair.second->run(*this, e);
}

void EntityManager::update() 
{
	for (auto pair : systems)
		pair.second->run(*this);
}

EntityManager::~EntityManager()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
		delete(*it);
	entities.clear();

	for (auto pair : components)
	{
		for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
			delete(*it);
		pair.second.clear();
	}
	components.clear();

	for (auto it = systems.begin(); it != systems.end(); ++it)
		delete (it->second);
	systems.clear();
}
