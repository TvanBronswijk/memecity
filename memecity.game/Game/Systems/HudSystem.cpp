#include "HudSystem.h"
#include "../Event/HealthEventArgs.h"
#include "../Event/ScoreEventArgs.h"
#include "../Event/ExpEventArgs.h"

void HudSystem::on_health_changed(memecity::engine::ecs::EntityManager& em, HealthEventArgs args) 
{
	std::string text = "Health:" + std::to_string(args.new_health);
	_hud->update("HEALTH", text);
}

void HudSystem::on_score_changed(memecity::engine::ecs::EntityManager& em, ScoreEventArgs args)
{
	std::string text = "Score:" + std::to_string(args.new_score);
	_hud->update("SCORE", text);
}

void HudSystem::on_exp_changed(memecity::engine::ecs::EntityManager& em, ExpEventArgs args)
{
	std::string text = "Exp:" + std::to_string(args.new_Exp);
	_hud->update("EXP", text);
}

void HudSystem::run(memecity::engine::ecs::EntityManager& em) const
{

}
