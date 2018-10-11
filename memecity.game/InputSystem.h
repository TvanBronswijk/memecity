#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include "../memecity.engine.ecs/System.h"

class InputSystem : public System
{
public:
	static std::string SYSTEM_TYPE;
	void run(EntityManager& em) override;
	std::string get_type() override;
};

#endif