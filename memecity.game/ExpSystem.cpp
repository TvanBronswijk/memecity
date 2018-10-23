#include "ExpSystem.h"
#include <string>
#include "ExpComponent.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "StatsComponent.h"
#include "Event.h"
#include "ExpEventArgs.h"


ExpSystem::ExpSystem()
{
}


ExpSystem::~ExpSystem()
{
}


std::string ExpSystem::get_type()
{
	return std::string("ExpSystem");
}

void ExpSystem::run(EntityManager& em)
{
}

void ExpSystem::run(EntityManager& em, EventArgs& e)
{
	const auto exp_event_args = static_cast<ExpEventArgs&>(e);
	auto players = em.get_entities_with_component(ExpComponent::COMPONENT_TYPE);

	for (auto & player : players)
	{
		ExpComponent* exp = dynamic_cast<ExpComponent*>(em.get_component_of_entity(player->id, ExpComponent::COMPONENT_TYPE));
		exp->exp = exp->exp += exp_event_args.exp;
		if (exp->exp >= exp->next_level)
		{
			auto stats = em.get_entities_with_component(StatsComponent::COMPONENT_TYPE);
			for (auto & stat : stats)
			{
				StatsComponent* stats = dynamic_cast<StatsComponent*>(em.get_component_of_entity(stat->id, StatsComponent::COMPONENT_TYPE));
				stats->strength++;
				exp->next_level = exp->next_level + exp->next_level / 10;
				exp->exp = 0;
			}
		}
	}
}
