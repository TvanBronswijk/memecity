#ifndef HUDSYSTEM_H
#define HUDSYSTEM_H

#include <ECS.h>
#include "UI/Overlay/Overlay.h"
#include "../Event/HealthEventArgs.h"
#include "../Event/ExpEventArgs.h"
#include "../Event/ScoreEventArgs.h"

struct BlikCoinEventArg;
struct StatsEventArgs;

class HudSystem : public memecity::engine::ecs::System
{
public:
	HudSystem(memecity::engine::ui::overlay::Overlay& overlay):_hud(&overlay)
	{
		//_hud = nullptr;
	}
	void on_health_changed(memecity::engine::ecs::EntityManager& em, HealthEventArgs args) ;
	void on_score_changed(memecity::engine::ecs::EntityManager& em, ScoreEventArgs args);
	void on_exp_changed(memecity::engine::ecs::EntityManager& em, ExpEventArgs args);
	void on_stats_changed(memecity::engine::ecs::EntityManager& em, StatsEventArgs args);
	void on_blikcoin_changed(memecity::engine::ecs::EntityManager& em, BlikCoinEventArg args);
	void run(memecity::engine::ecs::EntityManager& em) const override;
private:
	memecity::engine::ui::overlay::Overlay* _hud;
};
#endif // HUDSYSTEM_H
