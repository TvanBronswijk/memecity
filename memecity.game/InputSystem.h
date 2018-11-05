#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include "InputManager.h"
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "AIComponent.h"
#include "PositionComponent.h"
#include "InteractionEventArgs.h"
#include "AttackEventArgs.h"
#include "AttackEvent.h"
#include "InteractionSystem.h"
#include "Event.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"


class InputSystem : public System
{
	static std::string SYSTEM_TYPE;
private:
	std::weak_ptr<InputManager> input_manager;
	InteractionEvent* interaction_event;
	AttackEvent* attack_event;
	bool check_collision(EntityManager& em, Component* component, int range);
public:
	InputSystem(std::weak_ptr<InputManager> input_manager, InteractionEvent* interaction_event, AttackEvent* attack_event);
	void run(EntityManager& em) override;
	std::string get_type() override;
	void run(EntityManager& em, EventArgs& e) override;
};

#endif