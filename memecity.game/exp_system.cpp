#include "exp_system.h"
#include <string>
#include "exp_component.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "stats_component.h"


exp_system::exp_system()
{
}


exp_system::~exp_system()
{
}

bool exp_system::is_on_event(Event* e)
{
	return true;
}

std::string exp_system::get_type()
{
	return std::string("exp_system");
}

void exp_system::run(EntityManager& em)
{
}

void exp_system::run(EntityManager& em, Event* e)
{

	int add_exp = 10;
	int 

	auto players = em.get_entities_with_component(exp_component::COMPONENT_TYPE);

	for (auto & player : players)
	{
		exp_component* exp = dynamic_cast<exp_component*>(em.get_component_of_entity(player->id, exp_component::COMPONENT_TYPE));
		exp->exp = exp->exp += add_exp;
		if(exp->exp >= exp->next_level)
		{
			auto stats = em.get_entities_with_component(stats_component::COMPONENT_TYPE);
			for (auto & stat : stats)
			{
				stats_component* stats = dynamic_cast<stats_component*>(em.get_component_of_entity(stat->id, stats_component::COMPONENT_TYPE));
				stats->strength++;
				exp->next_level = exp->next_level + exp->next_level / 10;
			}
		}
	}
	//event to add exp

}
