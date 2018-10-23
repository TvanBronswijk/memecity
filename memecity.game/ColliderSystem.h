#ifndef _COLLIDERSYSTEM_H
#define  _COLLIDERSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"

class ColliderSystem : public System
{
	static std::string SYSTEM_TYPE;
public:
	bool is_on_event(Event *e) override;
	void run(EntityManager& em) override;
	std::string get_type() override;
	void run(EntityManager &em, Event *e) override;
};

#endif