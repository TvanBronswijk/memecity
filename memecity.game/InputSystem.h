#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"


class InputSystem : public ecs::System
{
private:
	std::weak_ptr<InputManager> input_manager;
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	InputSystem(std::weak_ptr<InputManager> input_manager);
	void run(ecs::EntityManager& em) override;
	ecs::system_typetoken get_type_token() override { return InputSystem::SYSTEM_TYPE; }
};

#endif