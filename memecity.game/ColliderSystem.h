#ifndef _COLLIDERSYSTEM_H
#define  _COLLIDERSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "ColliderEventArgs.h"
#include "ColliderEvent.h"
#include "ColliderComponent.h"

class ColliderEvent;

class ColliderSystem : public System
{
	static std::string SYSTEM_TYPE;
private:
	ColliderEvent *collider_event;
public:
	ColliderSystem(ColliderEvent *collider_event);
	~ColliderSystem();
	void run(EntityManager& em) override;
	std::string get_type() override;
	void run(EntityManager &em, const EventArgs& e) override;
};

#endif