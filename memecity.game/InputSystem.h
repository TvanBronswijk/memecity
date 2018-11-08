﻿#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include "../memecity.engine/InputManager.h"
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"


class InputSystem : public ecs::System
{
private:
	InputManager &input_manager;
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	InputSystem(InputManager& input_manager);
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return InputSystem::SYSTEM_TYPE; }
};

#endif