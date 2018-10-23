#ifndef _AISYSTEM_H
#define  _AISYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "PositionComponent.h"
#include "velocityComponent.h"
#include "AIComponent.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include <cstdlib>

class AISystem : public System {

	static std::string SYSTEM_TYPE;

private:
	int random_x(VelocityComponent* velocity);
	int random_y(VelocityComponent* velocity);
	void move_sprites();
	void check_health();
public:
	AISystem();

	bool is_on_event(Event *e) override;
	std::string get_type() override;
	void run(EntityManager &em) override;
	void run(EntityManager &em, Event *e) override;
	void move_random(Entity* element, EntityManager em);
};

#endif
