#ifndef _QUESTSYSTEM_H
#define  _QUESTSYSTEM_H
#include <ECS.h>
#include "..\..\GameManager.h"
#include "..\Components\QuestComponent.h"
#include "..\Components\TaskComponent.h"

class QuestSystem : public memecity::engine::ecs::System
{
private:
	memecity::engine::MultimediaManager& multimedia_manager;
public:
	QuestSystem(memecity::engine::MultimediaManager& multimedia_manager) : multimedia_manager(multimedia_manager) {}
	QuestSystem(const QuestSystem& qs) = default;
	void run(memecity::engine::ecs::EntityManager& em) const override;
	void story(const memecity::engine::ecs::Entity*) const;
	bool quest(QuestComponent*) const;
	bool task(TaskComponent*) const;
};
#endif
#pragma once
