
#ifndef EXPEVENTARGS_H
#define EXPEVENTARGS_H
#include <ECS.h>

struct ExpEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	int new_Exp;

	explicit ExpEventArgs(const int new_health) : new_Exp(new_health) {}
};
#endif // EXPEVENTARGS_H
