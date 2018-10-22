#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include <cstdlib>

class FightingSystem : public System {

	static std::string COMPONENT_TYPE;

public:
	FightingSystem();

	bool is_on_event(Event *e) override;
	std::string get_type() override;
	void run(EntityManager &em) override;
	void run(EntityManager &em, Event *e) override;
};

#endif