#ifndef _COMPONENT_H
#define  _COMPONENT_H
#include "Entity.h"
#include <string>

struct Component {
	int entity_id;

	Component(Entity* e) 
	{
		this->entity_id = e->id;
	}
	
	///<summary>Get the type of the component for filtering.</summary>
	virtual std::string get_type() = 0;
};

#endif