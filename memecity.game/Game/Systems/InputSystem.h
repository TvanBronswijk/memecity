#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include <ECS.h>
#include "..\..\GameManager.h"
#include "..\Event\AttackEventArgs.h"
#include "..\Event\InteractionEventArgs.h"

class InputSystem : public memecity::engine::ecs::System
{
private:
	GameManager::GameContext *_context;
	bool check_collision(BaseComponent& l, BaseComponent& r, int range) const;
public:
	memecity::engine::ecs::eventing::Event<InteractionEventArgs> interaction_event;
	memecity::engine::ecs::eventing::Event<AttackEventArgs> attack_event;

	InputSystem(GameManager::GameContext& context)
		: _context(&context) {}
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
};
#endif
