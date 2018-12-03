#include "HudSystem.h"
#include "../Event/HealthEventArgs.h"
#include "../Event/ScoreEventArgs.h"
#include "../Event/ExpEventArgs.h"
#include "../Event/StatsEventArgs.h"
#include "../Event/BlikCoinEventArg.h"

void HudSystem::on_health_changed(memecity::engine::ecs::EntityManager& em, HealthEventArgs args) 
{
	_hud->update("HEALTHVALUE", args.new_health);
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

void HudSystem::on_stats_changed(memecity::engine::ecs::EntityManager& em, StatsEventArgs args)
{
	_hud->update("S", "S: " + std::to_string(args.s));
	_hud->update("P", "P: " + std::to_string(args.p));
	_hud->update("E", "E: " + std::to_string(args.e));
	_hud->update("C", "C: " + std::to_string(args.c));
	_hud->update("I", "I: " + std::to_string(args.i));
	_hud->update("A", "A: " + std::to_string(args.a));
	_hud->update("L", "L: " + std::to_string(args.l));
}

void HudSystem::on_blikcoin_changed(memecity::engine::ecs::EntityManager& em, BlikCoinEventArg args)
{
	_hud->update("BLIKCOIN", "BlikCoin: " + std::to_string(args.new_coin));
}

void HudSystem::run(memecity::engine::ecs::EntityManager& em) const
{

}
