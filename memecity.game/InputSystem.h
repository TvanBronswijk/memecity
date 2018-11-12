#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include <ECS.h>
#include "InteractionEventArgs.h"
#include "AttackEventArgs.h"
#include "InputManager.h"

class InputSystem : public ecs::System
{
private:
	InputManager& input_manager;
	bool check_collision(ecs::EntityManager& em, ecs::Component& element, int range) const;
public:
	InputSystem(InputManager& input_manager)
		: input_manager(input_manager) {};
	void run(ecs::EntityManager& em) const override;
};
#endif
