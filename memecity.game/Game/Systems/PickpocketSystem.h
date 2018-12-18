#ifndef _PICKPOCKET_SYSTEM_H
#define _PICKPOCKET_SYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\PickpocketEventArgs.h"
#include "..\Event\BlikCoinEventArgs.h"
#include "..\Event\FaultyPickpocketEventArgs.h"
#include "..\Event\ExpEventArgs.h"

class PickpocketSystem : public memecity::engine::ecs::System
{
private:
	memecity::engine::MultimediaManager* multimedia_manager;
public:

	PickpocketSystem(memecity::engine::MultimediaManager& multimedia_manager)
		: multimedia_manager(&multimedia_manager) {}


	memecity::engine::ecs::eventing::Event<BlikCoinEventArgs> blikcoins_event;
	memecity::engine::ecs::eventing::Event<FaultyPickpocketEventArgs> faulty_pickpocket_event;
	memecity::engine::ecs::eventing::Event<ExpEventArgs> exp_event;

	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
	void on_pickpocket(memecity::engine::ecs::EntityManager& em, PickpocketEventArgs args);
};
#endif
