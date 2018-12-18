
#ifndef EXPEVENTARGS_H
#define EXPEVENTARGS_H
#include <ECS.h>

struct ExpEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	int new_exp, remaining_exp;

	explicit ExpEventArgs(int new_exp, int remaining_exp) : new_exp(new_exp), remaining_exp(remaining_exp) {}
};
#endif // EXPEVENTARGS_H
