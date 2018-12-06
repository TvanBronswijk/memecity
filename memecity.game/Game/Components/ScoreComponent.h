#ifndef _SCORE_COMPONENT_H
#define _SCORE_COMPONENT_H
#include <ECS.h>

struct ScoreComponent : public memecity::engine::ecs::Component
{
	int score;
	ScoreComponent(memecity::engine::ecs::Entity& entity)
		: ScoreComponent(entity, 0) {};
	ScoreComponent(memecity::engine::ecs::Entity& entity, int score)
		: memecity::engine::ecs::Component(entity), score(score) {};
};

#endif