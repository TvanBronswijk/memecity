#include "ExpSystem.h"
#include "ExpComponent.h"
#include "StatsComponent.h"
using namespace ecs;

void ExpSystem::run(EntityManager& em) const {}

void ExpSystem::on_exp_gain(EntityManager& em, int exp) const
{
	auto players = em.get_entities_with_component<ExpComponent>();

	for (auto & player : players)
	{
		auto exp_component = em.get_component_of_entity<ExpComponent>(player.get());
		exp_component->exp = exp_component->exp += exp;
		if (exp_component->exp >= exp_component->next_level)
		{
			auto stats_entities = em.get_entities_with_component<StatsComponent>();
			for (auto & stat : stats_entities)
			{
				auto stats = em.get_component_of_entity<StatsComponent>(stat.get());
				if (!stats)
					continue;
				stats->strength++;
				exp_component->next_level = exp_component->next_level + exp_component->next_level / 10;
				exp_component->exp = 0;
			}
		}
	}
}
