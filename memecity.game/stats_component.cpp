#include "stats_component.h"

std::string stats_component::COMPONENT_TYPE = "stats_component";

stats_component::stats_component(Entity* e): Component(e)
{
}


stats_component::~stats_component()
{
}

std::string stats_component::get_type()
{
	return  std::string("stats_component");
}
