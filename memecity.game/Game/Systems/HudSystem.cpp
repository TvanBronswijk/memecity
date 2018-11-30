#include "HudSystem.h"

void HudSystem::on_health_changed(memecity::engine::ecs::EntityManager& em, HealthChangedEventArgs args) 
{
	std::string text = "Health:" + std::to_string(args.new_health);
	_hud->update("HEALTH", text);
}

void HudSystem::run(memecity::engine::ecs::EntityManager& em) const
{

}
