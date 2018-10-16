#ifndef _LEVELCOMPONENT_H
#define  _LEVELCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct LevelComponent : public Component {

	static std::string COMPONENT_TYPE;

public:
	int _level;
	LevelComponent(Entity* e);
	LevelComponent(int _level, Entity* e);
	LevelComponent(int world, int range, Entity* e);
	std::string get_type() override;
};

#endif

