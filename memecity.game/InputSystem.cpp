#include "InputSystem.h"

std::string InputSystem::SYSTEM_TYPE = "InputSystem";

void InputSystem::run(EntityManager& em)
{

}

std::string InputSystem::get_type()
{
	return SYSTEM_TYPE;
}
