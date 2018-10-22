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

vector<Entity*> EntityManager::get_entities()
{
	return entities;
}

vector<Entity*> EntityManager::get_entities_with_component(string type)
{
	vector<Entity*> result;
	for (auto it = entities.begin(); it != entities.end(); ++it)
		if (this->has_component(*it, type))
			result.push_back(*it);
	return result;
}

vector<Component*> EntityManager::get_components_of_type(string type)
{
	return components[type];
}

Component* EntityManager::get_component_of_entity(int entity_id, string type)
{
	for (auto pairs : components)
		for (auto c : pairs.second)
			if (c->entity_id == entity_id && c->get_type() == type)
				return c;
	return nullptr;
}

vector<Component*> EntityManager::get_components_of_entity(int entity_id)
{
	vector<Component*> result;
	for (auto pairs : components)
		for (auto c : pairs.second)
			if (c->entity_id == entity_id)
				result.push_back(c);
	return result;
}

bool EntityManager::has_component(Entity* e, string type) 
{
	auto c = components[type];
	for (auto it = c.begin(); it != c.end(); ++it)
		if ((*it)->entity_id == e->id)
			return true;
	return false;
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
