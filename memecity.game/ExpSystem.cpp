#include "ExpSystem.h"

using namespace ecs;

system_typetoken ExpSystem::SYSTEM_TYPE = "ExpSystem";

ExpSystem::ExpSystem()
{
}

void ExpSystem::run(EntityManager& em)
{

}

void ExpSystem::on_exp_gain(EntityManager& em, int exp)
{
	auto players = em.get_entities_with_component(ExpComponent::COMPONENT_TYPE);

	for (auto & player : players)
	{
		ExpComponent* exp_component = dynamic_cast<ExpComponent*>(em.get_component_of_entity(player->id, ExpComponent::COMPONENT_TYPE));
		exp_component->exp = exp_component->exp += exp;
		if (exp_component->exp >= exp_component->next_level)
		{
			auto stats = em.get_entities_with_component(StatsComponent::COMPONENT_TYPE);
			for (auto & stat : stats)
			{
				StatsComponent* stats = dynamic_cast<StatsComponent*>(em.get_component_of_entity(stat->id, StatsComponent::COMPONENT_TYPE));
				stats->strength++;
				exp_component->next_level = exp_component->next_level + exp_component->next_level / 10;
				exp_component->exp = 0;
			}
		}
	}
}
