#ifndef _ENTITY_H
#define  _ENTITY_H

namespace ecs {
	struct Entity {
		int id;
		Entity(int id) : id(id)
		{
			this->id = id;
		}
	};
};

#endif