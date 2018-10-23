#include "StatsComponent.h"

std::string StatsComponent::COMPONENT_TYPE = "StatsComponent";

StatsComponent::StatsComponent(Entity* e): Component(e)
{
}


StatsComponent::~StatsComponent()
{
}

std::string StatsComponent::get_type()
{
	return  COMPONENT_TYPE;
}
