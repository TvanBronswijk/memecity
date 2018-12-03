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
	_hud->update("S", args.S);
	_hud->update("P", args.P);
	_hud->update("E", args.E);
	_hud->update("C", args.C);
	_hud->update("I", args.I);
	_hud->update("A", args.A);
	_hud->update("L", args.L);
}

void HudSystem::on_blikcoin_changed(memecity::engine::ecs::EntityManager& em, BlikCoinEventArg args)
{
	_hud->update("BLIKCOIN", "BlikCoin: " + std::to_string(args.new_coin));
}

void HudSystem::run(memecity::engine::ecs::EntityManager& em) const
{

}
