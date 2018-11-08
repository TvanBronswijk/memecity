#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include <ECS.h>
#include "AIComponent.h"
#include "PositionComponent.h"
#include "InteractionEventArgs.h"
#include "AttackEventArgs.h"
#include "Event.h"
#include "InputManager.h"


class InputSystem : public ecs::System
{
private:
	InputManager& input_manager;
	bool check_collision(ecs::EntityManager& em, ecs::Component& element, int range) const;
public:
	static ecs::system_typetoken SYSTEM_TYPE;
	InputSystem(InputManager& input_manager);
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return InputSystem::SYSTEM_TYPE; }

	ecs::eventing::Event<InteractionEventArgs> interaction_event;
	ecs::eventing::Event<AttackEventArgs> attack_event;
};

#endif