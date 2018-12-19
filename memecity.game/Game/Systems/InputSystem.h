#ifndef _INPUTSYSTEM_H
#define  _INPUTSYSTEM_H
#include <ECS.h>
#include "..\..\GameManager.h"
#include "..\Event\AttackEventArgs.h"
#include "..\Event\InteractionEventArgs.h"
#include "..\Event\QuestEventArgs.h"
#include "..\Event\PickpocketEventArgs.h"
#include "UI/Overlay/Overlay.h"

class InputSystem : public memecity::engine::ecs::System
{
private:
	GameManager::GameContext *_context;
	memecity::engine::ui::overlay::Overlay *_hud;
	bool check_collision(BaseComponent& l, BaseComponent& r, int range) const;
	int* _map_number;
	std::string* _save_slot;
public:
	memecity::engine::ecs::eventing::Event<InteractionEventArgs> interaction_event;
	memecity::engine::ecs::eventing::Event<AttackEventArgs> attack_event;
	memecity::engine::ecs::eventing::Event<QuestEventArgs> quest_event;
	memecity::engine::ecs::eventing::Event<PickpocketEventArgs> pickpocket_event;
	InputSystem(GameManager::GameContext& context, memecity::engine::ui::overlay::Overlay& hud, int& map_number, std::string& save_slot)
		: _context(&context), _hud(&hud),_map_number(&map_number), _save_slot(&save_slot) {}
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
};
#endif
