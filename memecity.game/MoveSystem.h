#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"

class MoveSystem : public System
{
	static std::string SYSTEM_TYPE;
public:
	bool is_on_event(Event *e) override;
	std::string get_type() override;
	void run(EntityManager& em) override;
	void run(EntityManager &em, Event *e) override;
};

#endif