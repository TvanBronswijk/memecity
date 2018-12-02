
#ifndef SCOREEVENTARGS_H
#define SCOREEVENTARGS_H
#include <ECS.h>

struct ScoreEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	const int new_score;

	ScoreEventArgs(const int new_score) : new_score(new_score) {}
};
#endif // SCOREEVENTARGS_H
