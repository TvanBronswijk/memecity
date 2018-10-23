#ifndef _EXP_COMPONENT_H
#define _EXP_COMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include <string>

struct ExpComponent: public Component
{
	static std::string COMPONENT_TYPE;

	
public:
	int exp = 0;
	int next_level = 0;
	ExpComponent(Entity* e);
	std::string get_type() override;
	~ExpComponent();
};

#endif
