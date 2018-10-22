#include "exp_component.h"

std::string exp_component::COMPONENT_TYPE = "exp_component";

exp_component::exp_component(Entity* e): Component(e)
{
}

std::string exp_component::get_type()
{
	return std::string("exp_component");
}


exp_component::~exp_component()
{
}
