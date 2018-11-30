#include "HudSystem.h"

void HudSystem::on_health_changed(memecity::engine::ecs::EntityManager& em, HealthChangedEventArgs args) 
{
	//_hud->update("HEALTH", "HEALTH: " + args.new_health);
}

void HudSystem::run(memecity::engine::ecs::EntityManager& em) const
{

}
