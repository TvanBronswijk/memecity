#ifndef _HEALTHSYSTEM_H
#define  _HEALTHSYSTEM_H
#include <ECS.h>
#include "..\Components.h"

class HealthSystem : public memecity::engine::ecs::System
{
public:
	memecity::engine::MultimediaManager& multimedia_manager;
	
	HealthSystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(multimedia_manager) {}

	void run(memecity::engine::ecs::EntityManager& em) const override;
	void on_damage(memecity::engine::ecs::EntityManager& em, std::reference_wrapper<const memecity::engine::ecs::Entity> entity);
};

#endif
