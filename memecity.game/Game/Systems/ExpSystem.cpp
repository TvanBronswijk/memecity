#include "ExpSystem.h"

using namespace memecity::engine::ecs;

void ExpSystem::run(EntityManager& em) const {}

void ExpSystem::on_exp_gain(EntityManager& em, int exp) const
{
	auto players = em.get_entities_with_component<ExpComponent>();

	for (auto& player : players)
	{
		auto exp_component = player.get().get<ExpComponent>();
		exp_component->exp += exp;
		if (exp_component->exp >= exp_component->next_level)
		{
			auto stats = player.get().get<StatsComponent>();
			stats->strength++;
			exp_component->next_level *= 1.1;
			exp_component->exp = 0;
		}
	}
}
