#include "ExpSystem.h"
#include "..\Components\StatsComponent.h"

using namespace memecity::engine::ecs;

void ExpSystem::run(EntityManager& em, float dt) const {}

void ExpSystem::on_exp_gain(EntityManager& em, ExpEventArgs args) 
{
	auto players = em.get_entities_with_component<ExpComponent>();

	for (auto& player : players)
	{
		auto exp_component = player.get().get<ExpComponent>();
		auto stats = player.get().get<StatsComponent>();
		
		exp_component->total_exp += args.new_exp;


		int remaining_exp = args.new_exp;

		while (remaining_exp > 0)
		{
			if (exp_component->exp + remaining_exp >= exp_component->next_level) {
				remaining_exp -= (exp_component->next_level - exp_component->exp);
				//TODO:: up the vailable points

				exp_component->exp = 0;
				exp_component->next_level *= 1.1;

			}
			else {
				exp_component->exp += remaining_exp;
				remaining_exp = 0;
			}
		}
		
		this->exp_event.fire(em, ExpEventArgs(exp_component->exp, exp_component->next_level));

	}
}
