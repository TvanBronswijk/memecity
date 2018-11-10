#ifndef _ENTITY_H
#define  _ENTITY_H
namespace ecs {
	struct Entity {
		int id;
		Entity(int id) 
			: id(id) {}

		bool operator==(const Entity& e) const { return this->id == e.id; }
		bool operator!=(const Entity& e) const { return this->id != e.id; }
	};
};
#endif
