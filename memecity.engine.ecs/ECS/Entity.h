#ifndef _ENTITY_H
#define  _ENTITY_H

namespace ecs {
	struct Entity {
		int id;
		Entity(int id) : id(id)
		{
			this->id = id;
		}

		bool operator==(const Entity& e) const { return id == e.id; }
		bool operator!=(const Entity& e) const { return id != e.id; }
	};
};

#endif
