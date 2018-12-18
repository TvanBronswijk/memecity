#ifndef _QUESTSYSTEM_H
#define  _QUESTSYSTEM_H
#include <ECS.h>
#include "..\..\GameManager.h"
#include "..\Quest\Quest.h"
#include "..\Quest\Task.h"
#include "..\Quest\Story.h"
#include "..\Event\QuestEventArgs.h"
#include "..\Event\ExpEventArgs.h"
#include "..\Event\BlikCoinEventArgs.h"

class QuestSystem : public memecity::engine::ecs::System
{
private:
	memecity::engine::MultimediaManager& multimedia_manager;

	void check_task_dropping(QuestEventArgs args, Task& task);
	void check_task_finding(QuestEventArgs args, Task& task);
	void check_task_interaction(QuestEventArgs args, Task& task);
	void check_task_fighting(QuestEventArgs args, Task& task);

public:
	QuestSystem(memecity::engine::MultimediaManager& multimedia_manager) : multimedia_manager(multimedia_manager) {}
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
	void story(memecity::engine::ecs::EntityManager& em, Story&) const;
	bool quest(Quest&) const;
	bool task(Task&) const;

	void on_event(memecity::engine::ecs::EntityManager &em, QuestEventArgs args);


	memecity::engine::ecs::eventing::Event<BlikCoinEventArgs> blikcoins_event;
	memecity::engine::ecs::eventing::Event<ExpEventArgs> exp_event;

};
#endif
